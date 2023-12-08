#include "MenuProjetos.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

MenuProjetos::MenuProjetos(string nomeBancoDeDados, string nomeSchema, Projeto _projeto) : Menu(nomeBancoDeDados, nomeSchema), projeto(_projeto) {}

MenuProjetos::~MenuProjetos() {}

void MenuProjetos::printarOpcoes() {
    cout << "1 - Ver informações do projeto" << endl;
    cout << "2 - Adicionar tarefa" << endl;
    cout << "3 - Remover tarefa" << endl;
    cout << "4 - Listar tarefas" << endl;
    cout << "5 - Atualizar status da tarefa" << endl;
    cout << "6 - Sair" << endl;
}

bool MenuProjetos::executarEscolha( int escolha ) {
    switch (escolha) {
        case 1: {
            verInformacoes();
            return false;
        }

        case 2: {
            adicionarTarefa();
            return false;
        }

        case 3: {
            removerTarefa();
            return false;
        }

        case 4: {
            listarTarefas();
            return false;
        }

        case 5: {
            string nomeTarefa;
            cout << "Digite o nome da tarefa: ";
            cin >> nomeTarefa;
            atualizarStatusTarefa(nomeTarefa);
            return false;
        }

        case 6: {
            sair();
        }

        default: {
            cout << "Opção inválida!" << endl;
            break;
        }
    }
    return false;
}

void MenuProjetos::verInformacoes() {
    cout << "Nome: " << projeto.getNome() << endl;
    cout << "Descrição: " << projeto.getDescricao() << endl;
    cout << "Data de início: " << ctime(&projeto.getDataInicio()) << endl;
}

void MenuProjetos::adicionarTarefa() {
    string nomeTarefa, descricaoTarefa, stringPrazo, nomeUsuario;
    time_t prazo;

    cout << "Digite o nome da tarefa: ";
    cin >> nomeTarefa;

    cout << "Digite a descrição da tarefa: ";
    cin >> descricaoTarefa;

    cout << "Digite a data do prazo da tarefa: ";
    cin >> stringPrazo;

    cout << "Digite o usuário responsável pela tarefa: ";
    cin >> nomeUsuario;

    prazo = bancoDeDados.string_to_time_t(stringPrazo);


    Tarefa tarefa(-1, nomeTarefa, descricaoTarefa, prazo);
    tarefa.setUsuarioId(bancoDeDados.buscarUsuario(nomeUsuario).getId());
    bancoDeDados.conectar();
    tarefa.setId(bancoDeDados.generate_id("tarefa"));

    bancoDeDados.inserirTarefa(tarefa);
    cout << "Tarefa criada com sucesso!" << endl;
}

void MenuProjetos::removerTarefa() {
    string nomeTarefa;
    cout << "Digite o nome da tarefa: ";
    cin >> nomeTarefa;

    bancoDeDados.conectar();
    bancoDeDados.removerTarefa(nomeTarefa);
    bancoDeDados.desconectar();
}

void MenuProjetos::listarTarefas() {
    set<Tarefa> tarefas = projeto.getTarefas();

    cout << "Tarefas:" << endl;
    for (Tarefa tarefa : tarefas) {
        cout << tarefa.getTitulo() << endl;
    }
}

void MenuProjetos::atualizarStatusTarefa(string nomeTarefa) {
    int status_int;
    Status status;
    cout << "Digite o status da tarefa (0-Pendente, 1-EmAndamento, 2-Concluida): ";
    cin >> status_int;

    switch (status_int) {
        case 0: {
            status = Pendente;
            break;
        }

        case 1: {
            status = EmAndamento;
            break;
        }

        case 2: {
            status = Concluida;
            break;
        }

        default: {
            cout << "Opção inválida!" << endl;
            break;
        }
    }

    bancoDeDados.conectar();
    Tarefa tarefa = bancoDeDados.buscarTarefa(nomeTarefa);
    bancoDeDados.desconectar();

    

    tarefa.setStatus(status);

    bancoDeDados.conectar();
    bancoDeDados.atualizarTarefa(tarefa);
    bancoDeDados.desconectar();
}

void MenuProjetos::sair() {
    cout << "Saindo do projeto..." << endl;
    exit(0);
}
