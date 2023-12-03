#include "Senha.h"
#include <openssl/sha.h>

Senha::Senha( string senha ) : senha( senha ) {}


void Senha::generateSalt() {
    const int saltLength = 16;
    unsigned char buffer[saltLength];
    RAND_bytes(buffer, sizeof(buffer));
    string _salt(reinterpret_cast<char>(buffer), saltLength);
    salt = _salt;
}

void Senha::combinePasswordAndSalt() {
    senha = senha + salt;
}

void Senha::calculateSHA256() {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, senha.c_str(), senha.size());
    SHA256_Final(hash, &sha256);

    char hashHex[2 *SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashHex[i * 2], "%02x", hash[i]);
    }

    hashPassword = string(hashHex);
}

string Senha::getHashedPassword() {
    generateSalt();
    combinePasswordAndSalt();
    calculateSHA256();

    string finalPassword = salt + "." + hashPassword;
    senha = "";
    return finalPassword;
}

bool Senha::comparePassword(string inputPassword) {
    // Primeiro, armazena a senha original temporariamente
    string originalPassword = senha;

    // Define a senha da classe para a senha de entrada
    senha = inputPassword;

    // Combina a senha de entrada com o salt armazenado
    combinePasswordAndSalt();

    // Calcula o hash SHA-256 da senha de entrada combinada com o salt
    calculateSHA256();

    // Restaura a senha original da classe
    senha = originalPassword;

    // Compara o hash calculado com o hash armazenado
    return hashPassword == this->hashPassword;
}
