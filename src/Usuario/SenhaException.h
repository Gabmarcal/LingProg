#ifndef SENHAEXCEPTION_H
#define SENHAEXCEPTION_H

#include <exception>
#include <string>

using namespace std;


class SenhaException : public exception {
    public:
        SenhaException(const char* _msg) {
            msg = "Erro com a senha: " + string(_msg);
        }

        virtual const char* what() {
            return msg.c_str();
        }

    private:
        string msg;
};

#endif
