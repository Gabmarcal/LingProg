#include "Projeto.h"

Projeto::Projeto() : id(0), nome(""), descricao("") {
    dataInicio = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

Projeto::Projeto(int id, string nome, string descricao) : id(id), nome(nome), descricao(descricao) {
    dataInicio = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

// Getters e Setters
int Projeto::getId() const {
    return id;
}

void Projeto::setId(int novoId) {
    id = novoId;
}

string Projeto::getNome() const {
    return nome;
}

void Projeto::setNome(string novoNome) {
    nome = novoNome;
}

string Projeto::getDescricao() const {
    return descricao;
}

void Projeto::setDescricao(string novaDescricao) {
    descricao = novaDescricao;
}

time_t& Projeto::getDataInicio() {
    return dataInicio;
}

void Projeto::setDataInicio(time_t novaDataInicio) {
    dataInicio = novaDataInicio;
}

set<Tarefa> Projeto::getTarefas() const {
    return tarefas;
}

// Métodos

void Projeto::adicionarTarefa(Tarefa& tarefa) {
    tarefas.insert(tarefa);
}

void Projeto::removerTarefa(Tarefa& tarefa) {
    tarefas.erase(tarefa);
}