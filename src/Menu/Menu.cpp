#include "Menu.h"

#include <iostream>
#include <fstream>

using namespace std;

Menu::Menu(string nomeBancoDeDados, string nomeSchema) : bancoDeDados(nomeBancoDeDados) {
    bancoDeDados.conectar();
    bancoDeDados.criarTabelas(nomeSchema);

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
