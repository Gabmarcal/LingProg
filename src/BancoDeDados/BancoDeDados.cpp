#include "BancoDeDados.h"
#include "../Usuario/Senha.h"
#include "../Usuario/UsuarioException.h"

#include <fstream>
#include <sstream>
#include <regex>
#include <ctime>

BancoDeDados::BancoDeDados(string stringConexao) 
    : stringConexao(stringConexao) {}

// Conexão do banco de dados

void BancoDeDados::conectar() {
    
    int resultado = sqlite3_open(stringConexao.c_str(), &db);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
}

void BancoDeDados::desconectar() {
    int resultado = sqlite3_close(db);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
}

void BancoDeDados::criarTabelas(string arquivo) {
    ifstream file(arquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo " + arquivo);
    }

    // Ler o conteúdo do arquivo em uma string
    stringstream buffer;
    buffer << file.rdbuf();
    string script = buffer.str();

    char* errmsg;
    if (sqlite3_exec(db, script.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
        string error = errmsg;
        sqlite3_free(errmsg);  // Liberar a memória alocada por sqlite3_exec
        throw runtime_error(error);
    }
}




// Usuários




void BancoDeDados::inserirUsuario(Usuario& usuario) {
    int resultado;

    string sql = "INSERT INTO usuario (nome, email, senha) VALUES ('" + usuario.getNome() + "', '" + usuario.getEmail() + "', '" + usuario.getSenha() + "');";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        // Se o erro for UNIQUE constraint failed: usuario.email
        if (string(sqlite3_errmsg(db)).find("UNIQUE constraint failed: usuario.email") != string::npos) {
            throw UsuarioException(USUARIO_EMAIL_JA_CADASTRADO);
        }
        // Se o erro for UNIQUE constraint failed: usuario.nome
        else if (string(sqlite3_errmsg(db)).find("UNIQUE constraint failed: usuario.nome") != string::npos) {
            throw UsuarioException(USUARIO_NOME_JA_CADASTRADO);
        }
        else{
            throw BancoDeDadosException(sqlite3_errmsg(db));
        }
    }

}

void BancoDeDados::removerUsuario(Usuario& usuario) {
    int resultado;

    string sql = "DELETE FROM usuario WHERE email = '" + usuario.getEmail() + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

}

void BancoDeDados::atualizarUsuario(Usuario& usuario) {
    int resultado;

    string sql = "UPDATE usuario SET nome = '" + usuario.getNome() + "', senha = '" + usuario.getSenha() + "' WHERE email = '" + usuario.getEmail() + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

}

Usuario BancoDeDados::buscarUsuario(string nomeUsuario) {
    int resultado;
    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM usuario WHERE nome = '" + nomeUsuario + "';";

    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    
    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU USUÁRIO
        Usuario usuario(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // nome
            (char*) sqlite3_column_text(stmt, 2), // email
            (char*) sqlite3_column_text(stmt, 3)); // senha


        sqlite3_finalize(stmt);

        // Adicionando todas as tarefas em usuário

        sql = "SELECT * FROM tarefa WHERE usuario_id = '" + to_string(usuario.getId()) + "';";

        resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

        if (resultado != SQLITE_OK) {
            throw BancoDeDadosException(sqlite3_errmsg(db));
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Tarefa tarefa(
                sqlite3_column_int(stmt, 0), // id
                (char*) sqlite3_column_text(stmt, 1), // titulo
                (char*) sqlite3_column_text(stmt, 2), // descricao
                (Status) sqlite3_column_int(stmt, 3), // status
                (time_t) sqlite3_column_int(stmt, 4), // data_criacao
                (time_t) sqlite3_column_int(stmt, 5)); // data_prazo

            usuario.atribuirTarefa(tarefa);
        }

        sqlite3_finalize(stmt);
        return usuario;
    }
    else {  // NÃO ENCONTROU USUÁRIO
        throw UsuarioException(USUARIO_NAO_ENCONTRADO); 
    }
}

string BancoDeDados::idParaNomeUsuario(int id) {
    int resultado;
    sqlite3_stmt* stmt;


    string sql = "SELECT nome FROM usuario WHERE id = '" + to_string(id) + "';";

    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    
    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU USUÁRIO
        string nome = (char*) sqlite3_column_text(stmt, 0);

        sqlite3_finalize(stmt);

        return nome;
    }
    else {  // NÃO ENCONTROU USUÁRIO
        throw UsuarioException(USUARIO_NAO_ENCONTRADO); 
    }
}


vector<Usuario> BancoDeDados::listarUsuarios() {
    int resultado;
    sqlite3_stmt* stmt;
    vector<Usuario> usuarios;

    string sql = "SELECT * FROM usuario;";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Usuario usuario(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // nome
            (char*) sqlite3_column_text(stmt, 2), // email
            (char*) sqlite3_column_text(stmt, 3)); // senha

        usuarios.push_back(usuario);
    }

    sqlite3_finalize(stmt);

    return usuarios;
}




// Tarefas




void BancoDeDados::inserirTarefa(Tarefa& tarefa) {
    int resultado;

    string sql = "INSERT INTO tarefa (titulo, descricao, status, data_criacao, data_prazo, projeto_id, usuario_id) VALUES ('" + tarefa.getTitulo() + "', '" + tarefa.getDescricao() + "', '" + to_string(tarefa.getStatus()) + "', '" + to_string(tarefa.getDataCriacao()) + "', '"  + to_string(tarefa.getDataPrazo()) + "', '" + to_string(tarefa.getProjetoId()) + "', '" + to_string(tarefa.getUsuarioId()) +"');";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        // Se o erro for UNIQUE constraint failed: tarefa.titulo
        if (string(sqlite3_errmsg(db)).find("UNIQUE constraint failed: tarefa.titulo") != string::npos) {
            throw UsuarioException(TAREFA_JA_CADASTRADA);
        }
        else{
            throw BancoDeDadosException(sqlite3_errmsg(db));
        }
    }

}

void BancoDeDados::removerTarefa(string nomeTarefa) {
    int resultado;

    string sql = "DELETE FROM tarefa WHERE titulo = '" + nomeTarefa + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

}

void BancoDeDados::atualizarTarefa(Tarefa& tarefa) {
    int resultado;

    string sql = "UPDATE tarefa SET titulo = '" + tarefa.getTitulo() + "', descricao = '" + tarefa.getDescricao() + "', status = '" + to_string(tarefa.getStatus()) + "', data_criacao = '" + to_string(tarefa.getDataCriacao()) + "', data_prazo = '" + to_string(tarefa.getDataPrazo()) + "' WHERE id = '" + to_string(tarefa.getId()) + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

}

Tarefa BancoDeDados::buscarTarefa(string nomeTarefa) {
    int resultado;
    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM tarefa WHERE titulo = '" + nomeTarefa + "';";

    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    
    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU TAREFA
        Tarefa tarefa(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // titulo
            (char*) sqlite3_column_text(stmt, 2), // descricao
            (Status) sqlite3_column_int(stmt, 3), // status
            sqlite3_column_int(stmt, 4), // data_criacao
            sqlite3_column_int(stmt, 5)); // data_prazo

        tarefa.setProjetoId(sqlite3_column_int(stmt, 6)); // projeto_id
        tarefa.setUsuarioId(sqlite3_column_int(stmt, 7)); // usuario_id
        sqlite3_finalize(stmt);

        return tarefa;
    }
    else {  // NÃO ENCONTROU TAREFA
        throw BancoDeDadosException("Tarefa não encontrada"); 
    }
}

vector<Tarefa> BancoDeDados::listarTarefasDoProjeto() {
    int resultado;
    sqlite3_stmt* stmt;
    vector<Tarefa> tarefas;

    string sql = "SELECT * FROM tarefa;";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Tarefa tarefa(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // titulo
            (char*) sqlite3_column_text(stmt, 2), // descricao
            (Status) sqlite3_column_int(stmt, 3), // status
            sqlite3_column_int(stmt, 4), // data_criacao
            sqlite3_column_int(stmt, 5)); // data_prazo

        tarefas.push_back(tarefa);
    }

    sqlite3_finalize(stmt);

    return tarefas;
}



// Projetos




void BancoDeDados::inserirProjeto(Projeto& projeto) {
    int resultado;

    string sql = "INSERT INTO projeto (nome, descricao, data_inicio) VALUES ('" + projeto.getNome() + "', '" + projeto.getDescricao() + "', '" + to_string(projeto.getDataInicio()) + "');";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        // Se o erro for UNIQUE constraint failed: projeto.nome
        if (string(sqlite3_errmsg(db)).find("UNIQUE constraint failed: projeto.nome") != string::npos) {
            throw UsuarioException(PROJETO_JA_CADASTRADO);
        }
        else{
            throw BancoDeDadosException(sqlite3_errmsg(db));
        }
    }

}

void BancoDeDados::removerProjeto(string nomeProjeto) {
    int resultado;

    string sql = "DELETE FROM projeto WHERE nome = '" + nomeProjeto + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

}

void BancoDeDados::atualizarProjeto(Projeto& projeto) {
    int resultado;

    string sql = "UPDATE projeto SET nome = '" + projeto.getNome() + "', descricao = '" + projeto.getDescricao() + "', data_inicio = '" + to_string(projeto.getDataInicio()) + "' WHERE id = '" + to_string(projeto.getId()) + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

}

Projeto BancoDeDados::buscarProjeto(string nomeProjeto) {
    int resultado;
    sqlite3_stmt* stmt;


    string sql = "SELECT * FROM projeto WHERE nome = '" + nomeProjeto + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    
    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU PROJETO
        Projeto projeto(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // nome
            (char*) sqlite3_column_text(stmt, 2)); // descricao

        
        sqlite3_finalize(stmt);

        // Adicionando todas as tarefas em projeto

        sql = "SELECT * FROM tarefa WHERE projeto_id = '" + to_string(projeto.getId()) + "';";
        resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

        if (resultado != SQLITE_OK) {
            throw BancoDeDadosException(sqlite3_errmsg(db));
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Tarefa tarefa(
                sqlite3_column_int(stmt, 0), // id
                (char*) sqlite3_column_text(stmt, 1), // titulo
                (char*) sqlite3_column_text(stmt, 2), // descricao
                (Status) sqlite3_column_int(stmt, 3), // status
                (time_t) sqlite3_column_int(stmt, 4), // data_criacao
                (time_t) sqlite3_column_int(stmt, 5)); // data_prazo

            tarefa.setProjetoId(sqlite3_column_int(stmt, 6)); // projeto_id
            tarefa.setUsuarioId(sqlite3_column_int(stmt, 7)); // usuario_id

            projeto.adicionarTarefa(tarefa);
        }

        sqlite3_finalize(stmt);

        
        return projeto;
    }
    else {  // NÃO ENCONTROU PROJETO
        sqlite3_finalize(stmt);
        throw UsuarioException(PROJETO_NAO_ENCONTRADO);
    }
}

vector<Projeto> BancoDeDados::listarProjetos() {
    int resultado;
    sqlite3_stmt* stmt;
    vector<Projeto> projetos;

    string sql = "SELECT * FROM projeto;";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Projeto projeto(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // nome
            (char*) sqlite3_column_text(stmt, 2)); // descricao

        projetos.push_back(projeto);
    }

    sqlite3_finalize(stmt);

    return projetos;
}



// Métodos auxiliares




int BancoDeDados::generate_id(string table) {
    int resultado;
    sqlite3_stmt* stmt;
    int id;

    string sql = "SELECT MAX(id) FROM " + table + ";";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }

    else {
        throw BancoDeDadosException("Erro ao gerar id");
    }

    sqlite3_finalize(stmt);

    return id + 1;
}

void BancoDeDados::registrar(string nome, string email, string senha) {

    
    int id = generate_id("usuario");
    
    Usuario user_novo(id, nome, email, senha);
    inserirUsuario(user_novo);

    cout << "Usuário registrado com sucesso!\n";
}

Usuario* BancoDeDados::login(string email, string senha) {
    int resultado;
    sqlite3_stmt* stmt;
    Usuario* usuario;
    Senha hash_senha(senha);


    string sql = "SELECT * FROM usuario WHERE email = '" + email + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {
        if (hash_senha.comparePassword((char*) sqlite3_column_text(stmt, 3))) {
            usuario = new Usuario(
                sqlite3_column_int(stmt, 0), // id
                (char*) sqlite3_column_text(stmt, 1), // nome
                (char*) sqlite3_column_text(stmt, 2), // email
                (char*) sqlite3_column_text(stmt, 3)); // senha
        }
        else {
            sqlite3_finalize(stmt);
            throw UsuarioException(USUARIO_SENHA_INCORRETA);
        }
    }

    else {
        sqlite3_finalize(stmt);
        throw UsuarioException(USUARIO_NAO_ENCONTRADO);; 
    }
    
    sqlite3_finalize(stmt);
    
    // Adicionando todas as tarefas em usuário

    sql = "SELECT * FROM tarefa WHERE usuario_id = '" + to_string(usuario->getId()) + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }
    

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Tarefa tarefa(
            sqlite3_column_int(stmt, 0), // id
            (char*) sqlite3_column_text(stmt, 1), // titulo
            (char*) sqlite3_column_text(stmt, 2), // descricao
            (Status) sqlite3_column_int(stmt, 3), // status
            (time_t) sqlite3_column_int(stmt, 4), // data_criacao
            (time_t) sqlite3_column_int(stmt, 5)); // data_prazo
            


        usuario->atribuirTarefa(tarefa);
    }
    

    sqlite3_finalize(stmt);

    return usuario;
}


time_t BancoDeDados::string_to_time_t(string dataStr) { // Data no formato : DD/MM/AAAA
    dataStr = dataStr.substr(0, 10);
    int dia, mes, ano;

    try {
        dia = stoi(dataStr.substr(0, 2));
        mes = stoi(dataStr.substr(3, 2));
        ano = stoi(dataStr.substr(6, 4));
    }
    catch (invalid_argument& e) {
        throw UsuarioException(FORMATO_DATA_INVALIDO);
    }
    

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 0) {
        throw UsuarioException(DATA_INVALIDA);
    }

    struct tm dataTime;
    dataTime.tm_mday = dia;
    dataTime.tm_mon = mes - 1;
    dataTime.tm_year = ano - 1900;
    dataTime.tm_hour = 0;
    dataTime.tm_min = 0;
    dataTime.tm_sec = 0;
    dataTime.tm_isdst = -1;

    time_t dataTimeT = mktime(&dataTime);

    return dataTimeT;
}

// Verificar se o formato é de um email
bool BancoDeDados::verificarEmail(string email) {
    regex padrao_email("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");

    return regex_match(email, padrao_email);
}

// Verificar se a senha tem pelo menos 8 caracteres, 1 letra maiúscula, 1 letra minúscula e 1 número
bool BancoDeDados::verificarSenha(string senha) {
    regex padrao_senha("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");

    return regex_match(senha, padrao_senha);
}