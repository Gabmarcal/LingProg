#include "MenuLogado.h"

#include <iostream>

using namespace std;

MenuLogado::MenuLogado(string nomeBancoDeDados, string nomeSchema) : Menu(nomeBancoDeDados, nomeSchema) {}

MenuLogado::~MenuLogado() {}

void MenuLogado::printarOpcoes() {
    cout << "\n-- Menu Principal --\n";
    cout << "1 - Criar projeto\n";
    cout << "2 - Listar projetos\n";
    cout << "3 - Entrar em um projeto\n";
    cout << "0 - Sair\n";
    cout << "Escolha uma opção: ";
}

bool MenuLogado::executarEscolha(int escolha) {
    switch (escolha) {
        case 1:
            criarProjeto();
            break;

        case 2:
            listarProjetos();
            break;

        case 3:
            listarProjetos();
            return entrarProjeto();

        case 0:
            sair();
            break;

        default:
            cout << "\nOpção inválida! Por favor, tente novamente.\n";
            break;
    }
    return false;
}

Projeto MenuLogado::getProjeto() {
    return projeto;
}

void MenuLogado::criarProjeto() {
    cout << "\n-- Criar Projeto --\n";
    string nomeProjeto, descricaoProjeto;

    cout << "Digite o nome do projeto: ";
    getline(cin, nomeProjeto);

    cout << "Digite a descrição do projeto: ";
    getline(cin, descricaoProjeto);

    Projeto projeto(-1, nomeProjeto, descricaoProjeto);
    projeto.setId(bancoDeDados.generate_id("projeto"));

    bancoDeDados.inserirProjeto(projeto);
    cout << "\nProjeto '" << nomeProjeto << "' criado com sucesso!\n";
}

void MenuLogado::removerProjeto() {
    cout << "\n-- Remover Projeto --\n";
    string nomeProjeto;
    cout << "Digite o nome do projeto: ";
    getline(cin, nomeProjeto);

    bancoDeDados.removerProjeto(nomeProjeto);
    cout << "\nProjeto '" << nomeProjeto << "' removido com sucesso!\n";
}

void MenuLogado::listarProjetos() {
    cout << "\n-- Listar Projetos --\n";
    vector<Projeto> projetos = bancoDeDados.listarProjetos();

    cout << "Projetos disponíveis:\n";
    for (const Projeto& projeto : projetos) {
        cout << " - " << projeto.getNome() << endl;
    }
}

bool MenuLogado::entrarProjeto() {
    cout << "\n-- Entrar em Projeto --\n";
    string nomeProjeto;
    cout << "Digite o nome do projeto: ";
    getline(cin, nomeProjeto);

    projeto = bancoDeDados.buscarProjeto(nomeProjeto);
    cout << "\nEntrou no projeto '" << nomeProjeto << "'.\n";
    
    return true;
}

void MenuLogado::sair() {
    cout << "\nSaindo do sistema...\n";
    exit(0);
}