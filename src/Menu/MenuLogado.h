#ifndef MENULOGADO_H
#define MENULOGADO_H

#include "Menu.h"

class MenuLogado : public Menu {
    public:
        MenuLogado(string nomeBancoDeDados, string nomeSchema);
        virtual ~MenuLogado();
        virtual void printarOpcoes();
        virtual bool executarEscolha( int escolha );
        
    private:
        
        
};

#endif
