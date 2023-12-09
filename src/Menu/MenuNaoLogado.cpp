#include "MenuNaoLogado.h"

#include <iostream>

using namespace std;

MenuNaoLogado::MenuNaoLogado(string nomeBancoDeDados, string nomeSchema) : Menu(nomeBancoDeDados, nomeSchema) {}

MenuNaoLogado::~MenuNaoLogado() {}

void MenuNaoLogado::printarOpcoes() {
    cout << "\n-- Menu Não Logado --\n";
    cout << "Escolha uma opção:\n";
    cout << "1 - Login\n";
    cout << "2 - Registrar\n";
    cout << "0 - Sair\n";
    cout << "> "; // Prompt para entrada do usuário
}

bool MenuNaoLogado::executarEscolha(int escolha) {
    switch (escolha) {
        case 1:
            return login();

        case 2:
            registrar();
            break;

        case 0:
            sair();
            break;

        default:
            cout << "\nOpção inválida! Por favor, tente novamente.\n";
            break;
    }
    return false;
}

bool MenuNaoLogado::login() {
    cout << "\n-- Login --\n";
    string email, senha;

    cout << "Digite seu email: ";
    getline(cin, email);

    cout << "Digite sua senha: ";
    getline(cin, senha);

    bancoDeDados.login(email, senha);
    cout << "\nLogin realizado com sucesso!\n";
    return true;
}

void MenuNaoLogado::registrar() {
    cout << "\n-- Registrar Novo Usuário --\n";
    string nome, email, senha;

    cout << "Digite seu nome: ";
    getline(cin, nome);

    while(true) {
        cout << "Digite seu email: ";
        getline(cin, email);
        if (bancoDeDados.verificarEmail(email)) {
            break;
        }
        cout << "Email inválido! Por favor, digite um email válido.\n";
    }

    while(true) {
        cout << "Digite sua senha: ";
        getline(cin, senha);
        if (bancoDeDados.verificarSenha(senha)) {
            break;
        }
        cout << "Senha inválida!\n";
        cout << "A senha deve ter pelo menos 8 caracteres, contendo pelo menos uma letra maiúscula, uma letra minúscula e um número.\n";
    }

    bancoDeDados.registrar(nome, email, senha);
}

void MenuNaoLogado::sair() {
    cout << "\nSaindo do sistema...\n";
    exit(0);
}

