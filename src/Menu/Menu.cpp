#include "Menu.h"

#include <iostream>

using namespace std;

Menu::Menu(string nomeBancoDeDados, string nomeSchema) : bancoDeDados(nomeBancoDeDados) {
    bancoDeDados.conectar();
    bancoDeDados.criarTabelas(nomeSchema);
    bancoDeDados.desconectar();
    cout << "Tabelas criadas com sucesso." << endl;
}

Menu::~Menu() {}

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
