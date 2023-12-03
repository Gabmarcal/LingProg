#include "Senha.h"
#include "SenhaException.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <iomanip>

Senha::Senha( string senha ) : senha( senha ) {}


void Senha::generateSalt() {
    const int saltLength = 16;
    unsigned char buffer[saltLength];
    if (RAND_bytes(buffer, sizeof(buffer)) == 1) { // Se RAND_bytes retornar 1, a operação foi bem-sucedida
        salt.assign(reinterpret_cast<char*>(buffer), saltLength);
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
            std::ostringstream oss;
            for (unsigned int i = 0; i < lengthOfHash; ++i) {
                oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
            }

            EVP_MD_CTX_free(context);
            hashPassword = oss.str();
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
