#ifndef MENU_H
#define MENU_H

#include <string>

#include "../BancoDeDados/BancoDeDados.h"

using namespace std;

class Menu {
    public:
        Menu(string nomeBancoDeDados, string nomeSchema);
        virtual ~Menu();
        virtual void mostrarMenu();
        virtual void printarOpcoes() = 0;
        virtual bool executarEscolha( int escolha ) = 0;
    protected:
        BancoDeDados bancoDeDados;

};

#endif
