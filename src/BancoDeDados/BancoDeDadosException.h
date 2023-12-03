#ifndef EXCECAO_H
#define EXCECAO_H

#include <exception>
#include <string>   

using namespace std;


class BancoDeDadosException : public exception {
    public:
        BancoDeDadosException(const char* _msg) {
            msg = "Erro com o banco de dados: " + string(_msg);
        }

        virtual const char* what() const throw() {
            return msg.c_str();
        }
    
    private:
        string msg;
    
};

#endif