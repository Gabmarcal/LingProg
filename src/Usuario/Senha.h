#ifndef SENHA_H
#define SENHA_H

#include <openssl/rand.h>
#include <iostream>
#include <cstring>
#include <openssl/sha.h>

#include <string>

using namespace std;

class Senha {
    public:
        Senha( string senha );

        string getHashedPassword();
        bool comparePassword(string hashedPassword);

    private:
        void generateSalt();
        void combinePasswordAndSalt();
        void calculateSHA256();

        string senha;
        string hashPassword;
        string salt;

};


#endif