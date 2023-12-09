#ifndef UEXCECAO_H
#define UEXCECAO_H

#include <exception>
#include <string>   

using namespace std;

enum ErrosUsuario {
    USUARIO_NAO_ENCONTRADO,
    USUARIO_SENHA_INCORRETA,
    PROJETO_NAO_ENCONTRADO,
    USUARIO_EMAIL_JA_CADASTRADO,
    USUARIO_NOME_JA_CADASTRADO,
    PROJETO_JA_CADASTRADO,
    TAREFA_NAO_ENCONTRADA,
    TAREFA_JA_CADASTRADA,
    FORMATO_DATA_INVALIDO,
    DATA_INVALIDA
};

class UsuarioException : public exception {
    public:
        UsuarioException(ErrosUsuario erro): erro(erro){
            switch (erro) {
                case USUARIO_NAO_ENCONTRADO:
                    msg = "Usuario nao encontrado";
                    break;
                case USUARIO_SENHA_INCORRETA:
                    msg = "Senha incorreta";
                    break;
                case PROJETO_NAO_ENCONTRADO:
                    msg = "Projeto nao encontrado";
                    break;
                case USUARIO_EMAIL_JA_CADASTRADO:
                    msg = "Email ja cadastrado";
                    break;
                case USUARIO_NOME_JA_CADASTRADO:
                    msg = "Nome ja cadastrado";
                    break;
                case PROJETO_JA_CADASTRADO:
                    msg = "Projeto ja cadastrado";
                    break;
                case TAREFA_NAO_ENCONTRADA:
                    msg = "Tarefa nao encontrada";
                    break;
                case TAREFA_JA_CADASTRADA:
                    msg = "Tarefa ja cadastrada";
                    break;
                case FORMATO_DATA_INVALIDO:
                    msg = "Formato de data invalido";
                    break;
                case DATA_INVALIDA:
                    msg = "Data invalida";
                    break;
            }
        }

        virtual const char* what() const throw() {
            return msg.c_str();
        }

        ErrosUsuario getErro() {
            return erro;
        }
    
    private:
        string msg;
        ErrosUsuario erro;
};

#endif