#ifndef MENUPROJETOS_H
#define MENUPROJETOS_H


#include "Menu.h"

class MenuProjetos : public Menu {
    public:
        MenuProjetos(string nomeBancoDeDados, string nomeSchema, Projeto _projeto);
        virtual ~MenuProjetos();
        virtual void printarOpcoes();
        virtual bool executarEscolha( int escolha );
        
    private:
        void verInformacoes();

        void adicionarTarefa();
        void removerTarefa();
        void listarTarefas();
        void atualizarStatusTarefa(string nomeTarefa);
        void informaçõesTarefa(string nomeTarefa);


        void sair();

        Projeto projeto;
        

        
};

#endif