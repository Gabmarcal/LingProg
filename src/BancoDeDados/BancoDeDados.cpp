#include "BancoDeDados.h"
#include "../Usuario/Senha.h"

#include <fstream>
#include <sstream>

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
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void BancoDeDados::removerUsuario(Usuario& usuario) {
    int resultado;

    string sql = "DELETE FROM usuario WHERE email = '" + usuario.getEmail() + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void BancoDeDados::atualizarUsuario(Usuario& usuario) {
    int resultado;

    string sql = "UPDATE usuario SET nome = '" + usuario.getNome() + "', senha = '" + usuario.getSenha() + "' WHERE email = '" + usuario.getEmail() + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
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
        sqlite3_close(db);

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

        return usuario;
    }
    else {  // NÃO ENCONTROU USUÁRIO
        throw BancoDeDadosException("Usuário não encontrado"); 
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
    sqlite3_close(db);

    return usuarios;
}




// Tarefas




void BancoDeDados::inserirTarefa(Tarefa& tarefa) {
    int resultado;

    string sql = "INSERT INTO tarefa (titulo, descricao, status, data_criacao, data_prazo) VALUES ('" + tarefa.getTitulo() + "', '" + tarefa.getDescricao() + "', '" + to_string(tarefa.getStatus()) + "', '" + to_string(tarefa.getDataCriacao()) + "', '" + to_string(tarefa.getDataPrazo()) + "');";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void BancoDeDados::removerTarefa(string nomeTarefa) {
    int resultado;

    string sql = "DELETE FROM tarefa WHERE titulo = '" + nomeTarefa + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void BancoDeDados::atualizarTarefa(Tarefa& tarefa) {
    int resultado;

    string sql = "UPDATE tarefa SET titulo = '" + tarefa.getTitulo() + "', descricao = '" + tarefa.getDescricao() + "', status = '" + to_string(tarefa.getStatus()) + "', data_criacao = '" + to_string(tarefa.getDataCriacao()) + "', data_prazo = '" + to_string(tarefa.getDataPrazo()) + "' WHERE id = '" + to_string(tarefa.getId()) + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
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

        sqlite3_finalize(stmt);
        sqlite3_close(db);

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
    sqlite3_close(db);

    return tarefas;
}



// Projetos




void BancoDeDados::inserirProjeto(Projeto& projeto) {
    int resultado;

    string sql = "INSERT INTO projeto (nome, descricao, data_inicio) VALUES ('" + projeto.getNome() + "', '" + projeto.getDescricao() + "', '" + to_string(projeto.getDataInicio()) + "');";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void BancoDeDados::removerProjeto(string nomeProjeto) {
    int resultado;

    string sql = "DELETE FROM projeto WHERE nome = '" + nomeProjeto + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void BancoDeDados::atualizarProjeto(Projeto& projeto) {
    int resultado;

    string sql = "UPDATE projeto SET nome = '" + projeto.getNome() + "', descricao = '" + projeto.getDescricao() + "', data_inicio = '" + to_string(projeto.getDataInicio()) + "' WHERE id = '" + to_string(projeto.getId()) + "';";
    resultado = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    sqlite3_close(db);
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
        sqlite3_close(db);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Tarefa tarefa(
                sqlite3_column_int(stmt, 0), // id
                (char*) sqlite3_column_text(stmt, 1), // titulo
                (char*) sqlite3_column_text(stmt, 2), // descricao
                (Status) sqlite3_column_int(stmt, 3), // status
                sqlite3_column_int(stmt, 4), // data_criacao
                sqlite3_column_int(stmt, 5)); // data_prazo

            projeto.adicionarTarefa(tarefa);
        }

        return projeto;
    }
    else {  // NÃO ENCONTROU PROJETO
        throw BancoDeDadosException("Projeto não encontrado"); 
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
    sqlite3_close(db);

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

    conectar();
    
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

    conectar();

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
            throw BancoDeDadosException("Senha incorreta");
        }
    }

    else {
        throw BancoDeDadosException("Usuário não encontrado"); 
    }
    
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
    sqlite3_close(db);

    return usuario;
}

time_t BancoDeDados::string_to_time_t(string data) {
    struct tm tm;
    time_t t;

    strptime(data.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
    t = mktime(&tm);

    return t;
}
