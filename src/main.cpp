#include <iostream>
#include <string>

#include "BancoDeDados/BancoDeDados.h"
#include "Menu/MenuNaoLogado.h"
#include "Menu/MenuLogado.h"
#include "Menu/MenuProjetos.h"
#include "Usuario/UsuarioException.h"

using namespace std;

int main() {
    Menu *menu;
    string nomeBancoDeDados = "bancoDeDados.db";
    string nomeSchema = "src/schema.sql";

    menu = new MenuNaoLogado(nomeBancoDeDados, nomeSchema);
    while (true) {
        try {
            menu->mostrarMenu();
            break; // Se tudo der certo, sair do loop
        }
        catch (const BancoDeDadosException& erro) {
            cout << erro.what() << endl;
            exit(1); // Encerra o programa em caso de erro no banco de dados
        } 
        catch (const UsuarioException& erro) {
            cout << erro.what() << endl;
            // Neste ponto, o loop continuará, permitindo uma nova tentativa
        }
    }


    delete menu;
    menu = new MenuLogado(nomeBancoDeDados, nomeSchema);
    while (true) {
        try {
            menu->mostrarMenu();
            break; // Se tudo der certo, sair do loop
        }
        catch (const BancoDeDadosException& erro) {
            cout << erro.what() << endl;
            exit(1); // Encerra o programa em caso de erro no banco de dados
        } 
        catch (const UsuarioException& erro) {
            cout << erro.what() << endl;
            // Neste ponto, o loop continuará, permitindo uma nova tentativa
        }
    }
    
    
    Projeto projeto = ((MenuLogado *) menu)->getProjeto();
    delete menu;
    menu = new MenuProjetos(nomeBancoDeDados, nomeSchema, projeto);
    while (true) {
        try {
            menu->mostrarMenu();
            break; // Se tudo der certo, sair do loop
        }
        catch (const BancoDeDadosException& erro) {
            cout << erro.what() << endl;
            exit(1); // Encerra o programa em caso de erro no banco de dados
        } 
        catch (const UsuarioException& erro) {
            cout << erro.what() << endl;
            // Neste ponto, o loop continuará, permitindo uma nova tentativa
        }
    }
    return 0;    
};