#include <iostream>
#include <string>

#include "BancoDeDados/BancoDeDados.h"

using namespace std;

int main() {

    int escolha;
    string email, senha, nome;
    BancoDeDados bancoDeDados("bancoDeDados.db");


    while (true) {
        cout << "Menu Principal:\n";
        cout << "1. login\n";
        cout << "2. Registrar\n";
        cout << "0. Sair\n";
        cin >> escolha;

        switch (escolha) {
            case 1: {
                cout << "Digite seu email: ";
                cin >> email;
                cout << "Digite sua senha: ";
                cin >> senha;

                bancoDeDados.login(email, senha);
                break;
            }

            case 2: {
                cout << "Digite seu nome: ";
                cin >> nome;
                cout << "Digite seu email: ";
                cin >> email;
                cout << "Digite sua senha: ";
                cin >> senha;

                bancoDeDados.registrar(nome, email, senha);
                break;
            }

            case 3:{
                bancoDeDados.conectar();
                bancoDeDados.criarTabelas("schema.sql");
                bancoDeDados.desconectar();
                cout << "Tabelas criadas com sucesso." << endl;
                break;
            }

            case 0: {
                cout << "Saindo...\n";
                return 0;
            }
        
            default: {
                cout << "Opção inválida!\n";
                break;
            }
        }
    }
};