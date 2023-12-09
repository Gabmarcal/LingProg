#ifndef TAREFA_H
#define TAREFA_H

#include <string>

using namespace std;

enum Status {Pendente, EmAndamento, Concluida};

class Tarefa {
    public:
        // Construtor
        Tarefa(int _id, string _titulo, string _descricao, time_t _dataPrazo);
        Tarefa(int _id, string _titulo, string _descricao, Status _status, time_t _dataCriacao, time_t _dataPrazo);

        // Getters
        int getId() const;
        int getProjetoId() const;
        int getUsuarioId() const;
        string getTitulo() const;
        string getDescricao() const;
        Status getStatus() const;
        string getStatusString() const;
        time_t getDataCriacao();
        time_t getDataPrazo();
        

        // Setters
        void setId(int id);
        void setProjetoId(int projeto_id);
        void setUsuarioId(int usuario_id);
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
        int projeto_id;
        int usuario_id;

        string titulo;
        string descricao;
        Status status;
        time_t dataCriacao;
        time_t dataPrazo;

};

#endif
