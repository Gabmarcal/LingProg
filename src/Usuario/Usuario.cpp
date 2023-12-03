#include "Usuario.h"
#include "Senha.h"

Usuario::Usuario(int id, string nome, string email, string senha) : id(id), nome(nome), email(email) {
    Senha senha_hash(senha);
    senha = senha_hash.getHashedPassword();
}

// Getters

int Usuario::getId() const {
    return id;
}

string Usuario::getNome() const {
    return nome;
}

string Usuario::getEmail() const {
    return email;
}

string Usuario::getSenha() const {
    return senha;
}

// Setters

void Usuario::setId(int id) {
    this->id = id;
}

void Usuario::setNome(string nome) {
    this->nome = nome;
}

void Usuario::setEmail(string email) {
    this->email = email;
}

void Usuario::setSenha(string senha) {
    this->senha = senha;
}

// Tarefas

void Usuario::atribuirTarefa(Tarefa& tarefa) {
    tarefasAtribuidas.insert(tarefa);
}

void Usuario::removerTarefa(Tarefa& tarefa) {
    tarefasAtribuidas.erase(tarefa);
}

// Métodos