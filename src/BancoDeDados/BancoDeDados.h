#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

#include "../Usuario/Usuario.h"
#include "../Tarefa/Tarefa.h"
#include "../Projeto/Projeto.h"
#include "BancoDeDadosException.h"

#include <string>
#include <iostream>
#include <sqlite3.h>

using namespace std;


class BancoDeDados {
    public:
        BancoDeDados(string stringConexao);

        // Conexão do banco de dados
        void conectar();
        void desconectar();
        void criarTabelas(string arquivo);

        // Usuários
        void inserirUsuario(Usuario& usuario);
        void removerUsuario(Usuario& usuario);
        void atualizarUsuario(Usuario& usuario);
        void buscarUsuario(Usuario& usuario);
        
        // Tarefas
        void inserirTarefa(Tarefa& tarefa);
        void removerTarefa(Tarefa& tarefa);
        void atualizarTarefa(Tarefa& tarefa);
        void buscarTarefa(Tarefa& tarefa);

        // Projetos
        void inserirProjeto(Projeto& projeto);
        void removerProjeto(Projeto& projeto);
        void atualizarProjeto(Projeto& projeto);
        void buscarProjeto(Projeto& projeto);
        
        // Métodos auxiliares
        Usuario* login(string nome, string senha);
        void registrar(string nome, string email, string senha);
        int generate_id(string table);

    private:
        string stringConexao;
        sqlite3* db;
};


#endif