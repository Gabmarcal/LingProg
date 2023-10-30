#include <sqlite3.h>
#include <iostream>

sqlite3* db;
int rc;

void inserirCliente(std::string nome, std::string email, std::string telefone) {
    std::string sql = "INSERT INTO clientes (nome, email, telefone) VALUES ('" + nome + "', '" + email + "', '" + telefone + "');";
    char* errorMsg;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);
    if(rc != SQLITE_OK) {
        std::cerr << "Erro SQL: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
    } else {
        std::cout << "Registro inserido com sucesso!" << std::endl;
    }
}

static int callback(void* notUsed, int argc, char** argv, char** azColName) {
    for(int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

void consultarClientes() {
    std::string sql = "SELECT * FROM clientes;";
    char* errorMsg;
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errorMsg);
    if(rc != SQLITE_OK) {
        std::cerr << "Erro SQL: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
    }
}

void deletarCliente(int id) {
    std::string sql = "DELETE FROM clientes WHERE id = " + std::to_string(id) + ";";
    char* errorMsg;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);
    if(rc != SQLITE_OK) {
        std::cerr << "Erro SQL: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
    } else {
        std::cout << "Registro deletado com sucesso!" << std::endl;
    }
}

int main() {
    rc = sqlite3_open("lingprog.db", &db);
    if(rc) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    } else {
        std::cout << "Conexão com o banco de dados estabelecida com sucesso." << std::endl;
    }
    
    std::string nome, email, telefone;
    std::cout << "Digite o nome do cliente: ";
    std::getline(std::cin, nome);
    std::cout << "Digite o email do cliente: ";
    std::getline(std::cin, email);
    std::cout << "Digite o telefone do cliente: ";
    std::getline(std::cin, telefone);
    inserirCliente(nome, email, telefone);
    consultarClientes();
    deletarCliente(1);
    consultarClientes();

    sqlite3_close(db);

    return 0;
}