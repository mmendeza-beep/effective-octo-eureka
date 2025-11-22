#include "Database.h"
#include <iostream>

Database::Database(const std::string& dbPath) : db(nullptr), dbPath(dbPath) {}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::initialize() {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    const char* createTableSQL = 
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "usuario TEXT NOT NULL UNIQUE,"
        "clave TEXT NOT NULL"
        ");";
    
    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool Database::validateUser(const std::string& email, const std::string& password) {
    const char* selectSQL = "SELECT clave FROM usuarios WHERE usuario = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    
    bool isValid = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* storedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (storedPassword && password == storedPassword) {
            isValid = true;
        }
    }
    
    sqlite3_finalize(stmt);
    return isValid;
}
