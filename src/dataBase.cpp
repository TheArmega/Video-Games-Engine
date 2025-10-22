#include "dataBase.h"
#include <iostream>

const std::string TABLE_CREATION_QUERY = R"(
    CREATE TABLE IF NOT EXISTS CIRCLES(
        ID INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        render INTEGER NOT NULL CHECK (render IN (0, 1)),
        radius REAL NOT NULL,
        mass REAL NOT NULL,
        xPos REAL NOT NULL,
        yPos REAL NOT NULL,
        xVel REAL NOT NULL,
        yVel REAL NOT NULL,
        r INTEGER NOT NULL,
        g INTEGER NOT NULL,
        b INTEGER NOT NULL
    );
)";

DataBase::DataBase(std::string _dbFile) : dbFile(_dbFile) {
  checkDbExist(dbFile);
}

// Setters
void DataBase::setDbFile(std::string f) { dbFile = f; }

// Getters
std::string DataBase::getDbFile() { return dbFile; }

// Methods
void DataBase::checkDbExist(std::string f) {
  int exit = sqlite3_open(f.c_str(), &db);

  if (exit != SQLITE_OK) {
    std::cerr << "Error opening DB" << sqlite3_errmsg(db) << std::endl;
    return;
  } else
    std::cout << "Opened DB succesfully" << std::endl;
  sqlite3_close(db);
}

void DataBase::createTable(std::string t) {
  int exit = sqlite3_open(dbFile.c_str(), &db);

  if (exit != SQLITE_OK) {
    std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
    return;
  }
  char *messageError;
  exit = sqlite3_exec(db, t.c_str(), NULL, 0, &messageError);

  if (exit != SQLITE_OK) {
    std::cerr << "Error while creating table!" << std::endl;
    sqlite3_free(messageError);
  } else
    std::cout << "Table created successfully!" << std::endl;
  sqlite3_close(db);
}
