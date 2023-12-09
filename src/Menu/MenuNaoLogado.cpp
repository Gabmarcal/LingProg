#include "MenuNaoLogado.h"

#include <iostream>

using namespace std;

MenuNaoLogado::MenuNaoLogado(string nomeBancoDeDados, string nomeSchema) : Menu(nomeBancoDeDados, nomeSchema) {}

MenuNaoLogado::~MenuNaoLogado() {}


void MenuNaoLogado::printarOpcoes() {
    cout << "Menu não logado" << endl;
    cout << "Escolha uma opção:" << endl;
    cout << "1 - Login" << endl;
    cout << "2 - Registrar" << endl;
    cout << "0 - Sair" << endl;
}

bool MenuNaoLogado::executarEscolha(int escolha) {
    switch (escolha) {
        case 1: {
            if (login()) {
                return true;
            }
        }

        case 2: {
            registrar();
            return false;
        }

        case 0: {
            sair();
        }

        default: {
            cout << "Opção inválida!" << endl;
            break;
        }
    }
    return false;
}

bool MenuNaoLogado::login() {
    string email, senha;

    cout << "Digite seu email: ";
    getline(cin, email);
    cout << "Digite sua senha: ";
    getline(cin, senha);

    bancoDeDados.login(email, senha);
    cout << "Login realizado com sucesso!" << endl;
    return true;
}

void MenuNaoLogado::registrar() {
    string nome, email, senha;

    cout << "Digite seu nome: ";
    getline(cin, nome);

    while(true) {
        cout << "Digite seu email: ";
        getline(cin, email);
        if (bancoDeDados.verificarEmail(email)) {
            break;
        }
        cout << "Email inválido!" << endl;
    }

    while(true) {
        cout << "Digite sua senha: ";
        getline(cin, senha);
        if (bancoDeDados.verificarSenha(senha)) {
            break;
        }
        // Senha deve ter pelo menos 8 caracteres, contendo pelo menos uma letra maiúscula, uma letra minúscula e um número
        cout << "Senha inválida!" << endl;
        cout << "A senha deve ter pelo menos 8 caracteres, contendo pelo menos uma letra maiúscula, uma letra minúscula e um número" << endl;
    }

    bancoDeDados.registrar(nome, email, senha);
}

void MenuNaoLogado::sair() {
    cout << "Saindo..." << endl;
    exit(0);
}

