#ifndef TAREFA_H
#define TAREFA_H

#include <string>

using namespace std;

enum Status {Pendente, EmAndamento, Concluida};

class Tarefa {
    public:
        Tarefa(int _id, string _titulo, string _descricao, Status _status, time_t _dataCriacao, time_t _dataPrazo);

        // Getters
        int getId() const;
        string getTitulo() const;
        string getDescricao() const;
        Status getStatus() const;
        time_t getDataCriacao() const;
        time_t getDataPrazo() const;

        // Setters
        void setId(int id);
        void setTitulo(string titulo);
        void setDescricao(string descricao);
        void setStatus(Status status);
        void setDataCriacao(time_t dataCriacao);
        void setDataPrazo(time_t dataPrazo);

        // Métodos
        //void imprimir();

        // Sobrecarga de operadores
        bool operator < (const Tarefa& tarefa) const;

    private:
        int id;
        string titulo;
        string descricao;
        Status status;
        time_t dataCriacao;
        time_t dataPrazo;

};

#endif
