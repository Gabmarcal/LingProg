#ifndef MENULOGADO_H
#define MENULOGADO_H

#include "Menu.h"

class MenuLogado : public Menu {
    public:
        MenuLogado(string nomeBancoDeDados, string nomeSchema);
        virtual ~MenuLogado();
        virtual void printarOpcoes();
        virtual bool executarEscolha( int escolha );
        Projeto getProjeto();
        
    private:
        void criarProjeto();
        void removerProjeto();
        void listarProjetos();
        bool entrarProjeto();
        void sair();

        Projeto projeto;

        
};

#endif
