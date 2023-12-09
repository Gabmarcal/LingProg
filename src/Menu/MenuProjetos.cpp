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
    cout << "6 - Mostrar informações da tarefa" << endl;
    cout << "0 - Sair" << endl;
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
            listarTarefas();
            removerTarefa();
            return false;
        }

        case 4: {
            listarTarefas();
            return false;
        }

        case 5: {
            string nomeTarefa;
            listarTarefas();
            cout << "Digite o nome da tarefa: ";
            getline(cin, nomeTarefa);
            atualizarStatusTarefa(nomeTarefa);
            return false;
        }

        case 6: {
            string nomeTarefa;
            listarTarefas();
            cout << "Digite o nome da tarefa: ";
            getline(cin, nomeTarefa);
            informaçõesTarefa(nomeTarefa);
            return false;
        }

        case 0: {
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
    getline(cin, nomeTarefa);

    cout << "Digite a descrição da tarefa: ";
    getline(cin, descricaoTarefa);

    cout << "Digite a data do prazo da tarefa: ";
    getline(cin, stringPrazo);


    prazo = bancoDeDados.string_to_time_t(stringPrazo);

    cout << "Digite o usuário responsável pela tarefa: ";
    getline(cin, nomeUsuario);


    Tarefa tarefa(-1, nomeTarefa, descricaoTarefa, prazo);
    Usuario usuario = bancoDeDados.buscarUsuario(nomeUsuario);

    tarefa.setUsuarioId(usuario.getId());
    tarefa.setId(bancoDeDados.generate_id("tarefa"));
    tarefa.setProjetoId(projeto.getId());

    bancoDeDados.inserirTarefa(tarefa);
    projeto.adicionarTarefa(tarefa);
    cout << "Tarefa criada com sucesso!" << endl;
}

void MenuProjetos::removerTarefa() {
    string nomeTarefa;

    cout << "Digite o nome da tarefa: ";
    getline(cin, nomeTarefa);

    projeto.buscarTarefa(nomeTarefa);
    projeto.removerTarefa(nomeTarefa);
    bancoDeDados.removerTarefa(nomeTarefa);
}

void MenuProjetos::listarTarefas() {
    set<Tarefa> tarefas = projeto.getTarefas();
    cout << "LISTANDO TAREFAS" << endl;

    cout << "Tarefas:" << endl;
    for (Tarefa tarefa : tarefas) {
        cout << tarefa.getTitulo() << endl;
    }
}

void MenuProjetos::atualizarStatusTarefa(string nomeTarefa) {
    int status_int;
    string status_str;
    Status status;

    cout << "Digite o status da tarefa (0-Pendente, 1-EmAndamento, 2-Concluida): ";
    getline(cin, status_str);
    status_int = stoi(status_str);

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

    Tarefa tarefa = projeto.buscarTarefa(nomeTarefa);

    

    tarefa.setStatus(status);
    projeto.removerTarefa(nomeTarefa);
    projeto.adicionarTarefa(tarefa);

    bancoDeDados.atualizarTarefa(tarefa);
}

void MenuProjetos::informaçõesTarefa(string nomeTarefa) {
    Tarefa tarefa = projeto.buscarTarefa(nomeTarefa);

    cout << "Nome: " << tarefa.getTitulo() << endl;
    cout << "Descrição: " << tarefa.getDescricao() << endl;
    time_t dataCriacao = tarefa.getDataCriacao();
    cout << "Data de criação: " << ctime(&dataCriacao);

    time_t dataPrazo = tarefa.getDataPrazo();
    cout << "Prazo: " << ctime(&dataPrazo);
    cout << "Status: " << tarefa.getStatusString() << endl;
    cout << "Usuário responsável: " << bancoDeDados.idParaNomeUsuario(tarefa.getUsuarioId()) << endl;
}

void MenuProjetos::sair() {
    cout << "Saindo do projeto..." << endl;
    exit(0);
}
