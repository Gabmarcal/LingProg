#include "MenuLogado.h"

#include <iostream>

using namespace std;

MenuLogado::MenuLogado(string nomeBancoDeDados, string nomeSchema) : Menu(nomeBancoDeDados, nomeSchema) {}

MenuLogado::~MenuLogado() {}

void MenuLogado::printarOpcoes() {
    cout << "1 - Criar projeto" << endl;
    cout << "2 - Listar projetos" << endl;
    cout << "3 - Entrar em um projeto" << endl;
    cout << "0 - Sair" << endl;
}

bool MenuLogado::executarEscolha( int escolha ) {
    switch (escolha) {
        case 1: {
            criarProjeto();
            return false;
        }

        case 2: {
            listarProjetos();
            return false;
        }

        case 3: {
            listarProjetos();
            return entrarProjeto();
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

Projeto MenuLogado::getProjeto() {
    return projeto;
}

void MenuLogado::criarProjeto() {
    string nomeProjeto, descricaoProjeto;


    cout << "Digite o nome do projeto: ";
    getline(cin, nomeProjeto);

    cout << "Digite a descrição do projeto: ";
    getline(cin, descricaoProjeto);

    Projeto projeto(-1, nomeProjeto, descricaoProjeto );
    projeto.setId(bancoDeDados.generate_id("projeto"));

    
    bancoDeDados.inserirProjeto(projeto);
    cout << "Projeto criado com sucesso!" << endl;
}

void MenuLogado::removerProjeto() {
    string nomeProjeto;
    cout << "Digite o nome do projeto: ";
    getline(cin, nomeProjeto);

    bancoDeDados.removerProjeto(nomeProjeto);
}

void MenuLogado::listarProjetos() {
    vector<Projeto> projetos = bancoDeDados.listarProjetos();

    cout << "Projetos:" << endl;
    for (Projeto projeto : projetos) {
        cout << projeto.getNome() << endl;
    }
}

bool MenuLogado::entrarProjeto() {
    string nomeProjeto;
    cout << "Digite o nome do projeto: ";
    getline(cin, nomeProjeto);

    projeto = bancoDeDados.buscarProjeto(nomeProjeto);
    
    return true;
}

void MenuLogado::sair() {
    cout << "Saindo..." << endl;
    exit(0);
}