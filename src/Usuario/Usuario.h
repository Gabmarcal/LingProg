#ifndef USUARIO_H
#define USUARIO_H

#include "../Tarefa/Tarefa.h"


#include <string>
#include <set>


using namespace std;

class Usuario {
    public:
        Usuario(int _id, string _nome, string _email, string _senha);

        // Getters
        int getId() const;
        string getNome() const;
        string getEmail() const;
        string getSenha() const;

        // Setters
        void setId(int id);
        void setNome(string nome);
        void setEmail(string email);
        void setSenha(string senha);

        // Tarefas
        void atribuirTarefa(Tarefa& tarefa);
        void removerTarefa(Tarefa& tarefa);

        // Métodos

    private:
        int id;
        string nome;
        string email;
        string senha;
        set<Tarefa> tarefasAtribuidas;

};

#endif