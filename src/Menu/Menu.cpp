#include "Menu.h"

#include <iostream>

using namespace std;

Menu::Menu(string nomeBancoDeDados, string nomeSchema) : bancoDeDados(nomeBancoDeDados) {
    bancoDeDados.conectar();
    bancoDeDados.criarTabelas(nomeSchema);
    //cout << "Tabelas criadas com sucesso." << endl;
}

Menu::~Menu() {
    bancoDeDados.desconectar();
}

void Menu::mostrarMenu() {
    int escolha;

    while (true) {
        printarOpcoes();
        cin >> escolha;
        if ( executarEscolha(escolha) ) {
            break;
        }
    }
}
