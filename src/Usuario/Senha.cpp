#include "Senha.h"
#include "SenhaException.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <iomanip>

Senha::Senha( string senha ) : senha( senha ) {}


void Senha::generateSalt() {
    const int saltLength = 16;
    unsigned char buffer[saltLength];
    if (RAND_bytes(buffer, sizeof(buffer)) == 1) { 
        ostringstream hexStream;
        hexStream << hex << setfill('0');
        for (int i = 0; i < saltLength; ++i) {
            hexStream << setw(2) << static_cast<int>(buffer[i]);
        }
        salt = hexStream.str();
    } else {
        throw SenhaException("Erro ao gerar salt");
    }
}



void Senha::combinePasswordAndSalt() {
    senha = senha + salt;
}


void Senha::calculateSHA256() {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if (context != nullptr) {
        if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) &&
            EVP_DigestUpdate(context, senha.c_str(), senha.size()) &&
            EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
            // Converte hash para hexadecimal
            ostringstream oss;
            for (unsigned int i = 0; i < lengthOfHash; ++i) {
                oss << hex << setw(2) << setfill('0') << (int)hash[i];
            }

            EVP_MD_CTX_free(context);
            hashPassword = oss.str();
            return;
        }
    }
    

    EVP_MD_CTX_free(context); // Libera o contexto em caso de falha
    throw SenhaException("Erro ao calcular hash SHA-256");
}

string Senha::getHashedPassword() {
    generateSalt();
    combinePasswordAndSalt();
    calculateSHA256();

    string finalPassword = salt + "." + hashPassword;
    senha = "";
    return finalPassword;
}

bool Senha::comparePassword(string hashedPassword) {
    // Recupera o salt da senha armazenada
    salt = hashedPassword.substr(0, hashedPassword.find('.'));

    // Recupera o hash da senha armazenada
    hashedPassword = hashedPassword.substr(hashedPassword.find('.') + 1);

    // Combina a senha de entrada com o salt armazenado
    combinePasswordAndSalt();

    // Calcula o hash SHA-256 da senha de entrada combinada com o salt
    calculateSHA256();

    // Retorna true se os hashes forem iguais
    return hashPassword == hashedPassword;
}
