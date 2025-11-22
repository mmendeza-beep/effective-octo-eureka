#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& dbPath);
    ~Database();
    
    bool initialize();
    bool validateUser(const std::string& email, const std::string& password);
    
private:
    sqlite3* db;
    std::string dbPath;
};

#endif
