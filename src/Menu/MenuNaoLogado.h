#ifndef MENUNAOLOGADO_H
#define MENUNAOLOGADO_H

#include "Menu.h"

class MenuNaoLogado : public Menu {
    public:
        MenuNaoLogado(string nomeBancoDeDados, string nomeSchema);
        virtual ~MenuNaoLogado();
        virtual void printarOpcoes();
        virtual bool executarEscolha( int escolha );
        
    private:
        bool login();
        void registrar();
        void sair();
        
};

#endif