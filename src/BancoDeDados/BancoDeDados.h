#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

#include "../Usuario/Usuario.h"
#include "../Tarefa/Tarefa.h"
#include "../Projeto/Projeto.h"
#include "BancoDeDadosException.h"

#include <string>
#include <iostream>
#include <sqlite3.h>
#include <limits>

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
        Usuario buscarUsuario(string nomeUsuario);
        string idParaNomeUsuario(int id);
        vector<Usuario> listarUsuarios();
        
        // Tarefas
        void inserirTarefa(Tarefa& tarefa);
        void removerTarefa(string nomeTarefa);
        void atualizarTarefa(Tarefa& tarefa);
        Tarefa buscarTarefa(string nomeTarefa);
        vector<Tarefa> listarTarefasDoProjeto();

        // Projetos
        void inserirProjeto(Projeto& projeto);
        void removerProjeto(string nomeProjeto);
        void atualizarProjeto(Projeto& projeto);
        Projeto buscarProjeto(string nomeProjeto);
        vector<Projeto> listarProjetos();
        
        // Métodos auxiliares
        Usuario* login(string nome, string senha);
        void registrar(string nome, string email, string senha);
        int generate_id(string table);
        time_t string_to_time_t(string data);
        bool verificarEmail(string email);
        bool verificarSenha(string senha);

    private:
        string stringConexao;
        sqlite3* db;
};




#endif