#include <iostream>
#include <string>

#include "BancoDeDados/BancoDeDados.h"
#include "Menu/MenuNaoLogado.h"
#include "Menu/MenuLogado.h"
#include "Menu/MenuProjetos.h"

using namespace std;

int main() {
    Menu *menu;
    string nomeBancoDeDados = "bancoDeDados.db";
    string nomeSchema = "src/schema.sql";

    menu = new MenuNaoLogado(nomeBancoDeDados, nomeSchema);
    try {
        menu->mostrarMenu();
    } catch (exception *erro) {
        cout << erro->what() << endl;
        exit(1);
    }

    delete menu;
    menu = new MenuLogado(nomeBancoDeDados, nomeSchema);
    try {
        menu->mostrarMenu();
    } catch (exception *erro) {
        cout << erro->what() << endl;
        exit(1);
    }
    
    Projeto projeto = ((MenuLogado *) menu)->getProjeto();
    delete menu;
    menu = new MenuProjetos(nomeBancoDeDados, nomeSchema, projeto);
    try {
        menu->mostrarMenu();
    } catch (exception *erro) {
        cout << erro->what() << endl;
        exit(1);
    }

    return 0;    
};