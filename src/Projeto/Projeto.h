#ifndef PROJETO_H
#define PROJETO_H

#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <ctime>
#include "../Tarefa/Tarefa.h"

using namespace std;

class Projeto {
    public:
        Projeto();
        Projeto(int _id, string _nome, string _descricao);

        // Getters
        int getId() const;
        string getNome() const;
        string getDescricao() const;
        time_t& getDataInicio();
        set<Tarefa> getTarefas() const;

        // Setters
        void setId(int _id);
        void setNome(string _nome);
        void setDescricao(string _descricao);
        void setDataInicio(time_t _dataInicio);

        // Métodos
        void adicionarTarefa(Tarefa& tarefa);
        void removerTarefa(string nomeTarefa);

    private:
        int id;
        string nome;
        string descricao;
        time_t dataInicio;
        set<Tarefa> tarefas;
};
#endif
