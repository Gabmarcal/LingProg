#include "MenuProjetos.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

MenuProjetos::MenuProjetos(string nomeBancoDeDados, string nomeSchema, Projeto _projeto) 
    : Menu(nomeBancoDeDados, nomeSchema), projeto(_projeto) {}

MenuProjetos::~MenuProjetos() {}

void MenuProjetos::printarOpcoes() {
    cout << "\n-- Opções do Menu de Projeto --\n";
    cout << "1 - Ver informações do projeto\n";
    cout << "2 - Adicionar tarefa\n";
    cout << "3 - Remover tarefa\n";
    cout << "4 - Listar tarefas\n";
    cout << "5 - Atualizar status da tarefa\n";
    cout << "6 - Mostrar informações da tarefa\n";
    cout << "0 - Sair\n";
    cout << "Escolha uma opção: ";
}

bool MenuProjetos::executarEscolha(int escolha) {
    string nomeTarefa;

    switch (escolha) {
        case 1:
            verInformacoes();
            break;

        case 2:
            adicionarTarefa();
            break;

        case 3:
            listarTarefas();
            removerTarefa();
            break;

        case 4:
            listarTarefas();
            break;

        case 5:
            listarTarefas();
            cout << "Digite o nome da tarefa: ";
            getline(cin, nomeTarefa);
            atualizarStatusTarefa(nomeTarefa);
            break;

        case 6:
            listarTarefas();
            cout << "Digite o nome da tarefa: ";
            getline(cin, nomeTarefa);
            informaçõesTarefa(nomeTarefa);
            break;

        case 0:
            sair();
            break;

        default:
            cout << "Opção inválida!" << endl;
            break;
    }
    return false;
}

void MenuProjetos::verInformacoes() {
    cout << "\n-- Informações do Projeto --\n";
    cout << "Nome: " << projeto.getNome() << endl;
    cout << "Descrição: " << projeto.getDescricao() << endl;
    cout << "Data de início: " << ctime(&projeto.getDataInicio()) << endl;
}

void MenuProjetos::adicionarTarefa() {
    cout << "\n-- Adicionar Tarefa ao Projeto --\n";

    string nomeTarefa, descricaoTarefa, stringPrazo, nomeUsuario;
    time_t prazo;

    cout << "Digite o nome da tarefa: ";
    getline(cin, nomeTarefa);

    cout << "Digite a descrição da tarefa: ";
    getline(cin, descricaoTarefa);

    cout << "Digite a data do prazo da tarefa (DD/MM/AAAA): ";
    getline(cin, stringPrazo);
    prazo = bancoDeDados.string_to_time_t(stringPrazo);

    cout << "Digite o nome do usuário responsável pela tarefa: ";
    getline(cin, nomeUsuario);

    Tarefa tarefa(-1, nomeTarefa, descricaoTarefa, prazo);
    Usuario usuario = bancoDeDados.buscarUsuario(nomeUsuario);

    tarefa.setUsuarioId(usuario.getId());
    tarefa.setId(bancoDeDados.generate_id("tarefa"));
    tarefa.setProjetoId(projeto.getId());

    bancoDeDados.inserirTarefa(tarefa);
    projeto.adicionarTarefa(tarefa);

    cout << "Tarefa '" << nomeTarefa << "' criada com sucesso!\n";
}

void MenuProjetos::removerTarefa() {
    cout << "\n-- Remover Tarefa do Projeto --\n";

    string nomeTarefa;
    cout << "Digite o nome da tarefa que deseja remover: ";
    getline(cin, nomeTarefa);
    
    projeto.buscarTarefa(nomeTarefa);
    projeto.removerTarefa(nomeTarefa);
    bancoDeDados.removerTarefa(nomeTarefa);
    cout << "Tarefa '" << nomeTarefa << "' removida com sucesso!\n";
    
}

void MenuProjetos::listarTarefas() {
    set<Tarefa> tarefas = projeto.getTarefas();

    cout << "\nTarefas:" << endl;
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

    cout << "Status da tarefa '" << nomeTarefa << "' atualizado para " << tarefa.getStatusString() << ".\n";
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
