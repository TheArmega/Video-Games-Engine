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
        r INTEGER NOT NULL CHECK (r BETWEEN 0 AND 255),
        g INTEGER NOT NULL CHECK (g BETWEEN 0 AND 255),
        b INTEGER NOT NULL CHECK (b BETWEEN 0 AND 255)
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
bool DataBase::openDb() {
  int exit = sqlite3_open(dbFile.c_str(), &db);
  if (exit != SQLITE_OK) {
    std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }
  return true;
}

void DataBase::closeDb() {
  if (db) {
    sqlite3_close(db);
    db = nullptr;
  }
}

void DataBase::checkDbExist(std::string f) {
  if (openDb())
    std::cout << "DB available!" << std::endl;
  closeDb();
}

void DataBase::createTable(std::string t) {
  if (!openDb())
    return;

  char *messageError;
  int exit = sqlite3_exec(db, t.c_str(), NULL, 0, &messageError);

  if (exit != SQLITE_OK) {
    std::cerr << "Error while creating table!" << std::endl;
    sqlite3_free(messageError);
  } else
    std::cout << "Table created successfully!" << std::endl;

  closeDb();
}

void DataBase::insertCircle(Circle c) {
  if (!openDb())
    return;

  const char *sql = R"(
      INSERT INTO CIRCLES (name, render, radius, mass, xPos, yPos, xVel, yVel, r, g, b)
      VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
  )";

  sqlite3_stmt *stmt;
  int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (exit != SQLITE_OK) {
    std::cerr << "Error while preparing statement: " << sqlite3_errmsg(db)
              << std::endl;
    closeDb();
    return;
  }

  sqlite3_bind_text(stmt, 1, c.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, c.getRender() ? 1 : 0);
  sqlite3_bind_double(stmt, 3, c.getRadius());
  sqlite3_bind_double(stmt, 4, c.getMass());
  sqlite3_bind_double(stmt, 5, c.getXPos());
  sqlite3_bind_double(stmt, 6, c.getYPos());
  sqlite3_bind_double(stmt, 7, c.getXVel());
  sqlite3_bind_double(stmt, 8, c.getYVel());
  sqlite3_bind_int(stmt, 9, c.getRColor());
  sqlite3_bind_int(stmt, 10, c.getGColor());
  sqlite3_bind_int(stmt, 11, c.getBColor());

  exit = sqlite3_step(stmt);

  if (exit != SQLITE_DONE) {
    std::cerr << "Error while inserting query: " << sqlite3_errmsg(db)
              << std::endl;
  } else
    std::cout << "Circle inserted in table!" << std::endl;

  sqlite3_finalize(stmt);
  closeDb();
}

void DataBase::deleteCircle(Circle c) {
  if (!openDb())
    return;

  const char *sql = R"(
      DELETE FROM CIRCLES WHERE name = ?; 
    )";

  sqlite3_stmt *stmt;
  int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (exit != SQLITE_OK) {
    std::cerr << "Error while preparing statement: " << sqlite3_errmsg(db)
              << std::endl;
    closeDb();
    return;
  }

  sqlite3_bind_text(stmt, 1, c.getName().c_str(), -1, SQLITE_TRANSIENT);

  exit = sqlite3_step(stmt);
  if (exit != SQLITE_DONE) {
    std::cerr << "Error while deleting query: " << sqlite3_errmsg(db)
              << std::endl;
  } else
    std::cout << "Circle deleted from table!" << std::endl;

  sqlite3_finalize(stmt);
  closeDb();
}
