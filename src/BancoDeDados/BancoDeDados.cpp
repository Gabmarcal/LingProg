#include "BancoDeDados.h"
#include "../Usuario/Senha.h"

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

void BancoDeDados::buscarUsuario(Usuario& usuario) {
    int resultado;
    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM usuario WHERE id = '" + to_string(usuario.getId()) + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU USUÁRIO
        //usuario.setNome((char*) sqlite3_column_text(stmt, 1));
        //usuario.setSenha((char*) sqlite3_column_text(stmt, 3));
    }
    else {  // NÃO ENCONTROU USUÁRIO
        throw BancoDeDadosException("Usuário não encontrado"); 
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
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

void BancoDeDados::removerTarefa(Tarefa& tarefa) {
    int resultado;

    string sql = "DELETE FROM tarefa WHERE id = '" + to_string(tarefa.getId()) + "';";
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

void BancoDeDados::buscarTarefa(Tarefa& tarefa) {
    int resultado;
    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM tarefa WHERE id = '" + to_string(tarefa.getId()) + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU TAREFA
        //tarefa.setTitulo((char*) sqlite3_column_text(stmt, 1));
        //tarefa.setDescricao((char*) sqlite3_column_text(stmt, 2));
        //tarefa.setStatus((Status) sqlite3_column_int(stmt, 3));
        //tarefa.setDataCriacao(sqlite3_column_int(stmt, 4));
        //tarefa.setDataPrazo(sqlite3_column_int(stmt, 5));
    }
    else {  // NÃO ENCONTROU TAREFA
        throw BancoDeDadosException("Tarefa não encontrada"); 
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
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

void BancoDeDados::removerProjeto(Projeto& projeto) {
    int resultado;

    string sql = "DELETE FROM projeto WHERE id = '" + to_string(projeto.getId()) + "';";
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

void BancoDeDados::buscarProjeto(Projeto& projeto) {
    int resultado;
    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM projeto WHERE id = '" + to_string(projeto.getId()) + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {  // ENCONTROU PROJETO
        //projeto.setNome((char*) sqlite3_column_text(stmt, 1));
        //projeto.setDescricao((char*) sqlite3_column_text(stmt, 2));
        //projeto.setDataInicio(sqlite3_column_int(stmt, 3));
    }
    else {  // NÃO ENCONTROU PROJETO
        throw BancoDeDadosException("Projeto não encontrado"); 
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
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
    
    string hash_senha = Senha(senha).getHashedPassword();
    int id = generate_id("usuario");

    
    Usuario user_novo(id, nome, email, hash_senha);
    inserirUsuario(user_novo);

    cout << "Usuário registrado com sucesso!\n";
}

Usuario* BancoDeDados::login(string email, string senha) {
    int resultado;
    sqlite3_stmt* stmt;
    Usuario* usuario;

    string sql = "SELECT * FROM usuario WHERE email = '" + email + "';";
    resultado = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (resultado != SQLITE_OK) {
        throw BancoDeDadosException(sqlite3_errmsg(db));
    }

    resultado = sqlite3_step(stmt);

    if (resultado == SQLITE_ROW) {
        Senha senha_hash((char*) sqlite3_column_text(stmt, 3));

        if (senha_hash.comparePassword(senha)) {
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

    sql = "SELECT * FROM tarefa WHERE id_usuario = '" + to_string(usuario->getId()) + "';";
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

        usuario->atribuirTarefa(tarefa);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return usuario;
}