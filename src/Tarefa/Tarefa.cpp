#include "Tarefa.h"

#include <string>
#include <chrono>
#include <ctime>

using namespace std;

// Construtor
Tarefa::Tarefa(int id, string titulo, string descricao, time_t dataPrazo)
    : id(id), titulo(titulo), descricao(descricao), status(Pendente), dataPrazo(dataPrazo) {
    dataCriacao = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

Tarefa::Tarefa(int id, string titulo, string descricao, Status status, time_t dataCriacao, time_t dataPrazo) 
    : id(id), titulo(titulo), descricao(descricao), status(status), dataCriacao(dataCriacao), dataPrazo(dataPrazo) {}

// Getters e Setters
int Tarefa::getId() const {
    return id;
}

int Tarefa::getProjetoId() const {
    return projeto_id;
}

int Tarefa::getUsuarioId() const {
    return usuario_id;
}

void Tarefa::setId(int novoId) {
    id = novoId;
}

void Tarefa::setProjetoId(int novoProjetoId) {
    projeto_id = novoProjetoId;
}

void Tarefa::setUsuarioId(int novoUsuarioId) {
    usuario_id = novoUsuarioId;
}

string Tarefa::getTitulo() const {
    return titulo;
}

void Tarefa::setTitulo(string novoTitulo) {
    titulo = novoTitulo;
}

string Tarefa::getDescricao() const {
    return descricao;
}

void Tarefa::setDescricao(string novaDescricao) {
    descricao = novaDescricao;
}

Status Tarefa::getStatus() const {
    return status;
}

string Tarefa::getStatusString() const {
    switch (status) {
        case Pendente:
            return "Pendente";
        case EmAndamento:
            return "Em andamento";
        case Concluida:
            return "Concluída";
        default:
            return "Status inválido";
    }
}

void Tarefa::setStatus(Status novoStatus) {
    status = novoStatus;
}

time_t Tarefa::getDataCriacao() {
    return dataCriacao;
}

void Tarefa::setDataCriacao(time_t novaDataCriacao) {
    dataCriacao = novaDataCriacao;
}

time_t Tarefa::getDataPrazo() {
    return dataPrazo;
}

void Tarefa::setDataPrazo(time_t novoPrazo) {
    dataPrazo = novoPrazo;
}

// Sobrecarga de operadores

bool Tarefa::operator<(const Tarefa& tarefa) const {
    return id < tarefa.id;
}