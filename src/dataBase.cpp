/**
 * @file dataBase.cpp
 * @brief DataBase class implementation
 * @ingroup DataBaseModule
 *
 * Implements the DataBase constructor, destructor, move semantics,
 * setters, getters, and database methods.
 */

#include "dataBase.h"
#include <cstddef>
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

// =======================
// Constructor / Destructor
// =======================
DataBase::DataBase(std::string _dbFile) : dbFile(_dbFile) {
  checkDbExist(dbFile);
}

DataBase::~DataBase() { closeDb(); }

// =======================
// Move semantics
// =======================
DataBase::DataBase(DataBase &&other) noexcept
    : db(other.db), dbFile(std::move(other.dbFile)) {
  other.db = nullptr;
}

DataBase &DataBase::operator=(DataBase &&other) noexcept {
  if (this != &other) {
    closeDb();
    db = other.db;
    dbFile = std::move(other.dbFile);
    other.db = nullptr;
  }
  return *this;
}

// =======================
// Setters
// =======================
void DataBase::setDbFile(std::string f) { dbFile = f; }

// =======================
// Getters
// =======================
std::string DataBase::getDbFile() { return dbFile; }

// =======================
// Methods
// =======================
bool DataBase::openDb() {
  int exit = sqlite3_open(dbFile.c_str(), &db);
  if (exit != SQLITE_OK) {
    std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
    db = nullptr;
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

sqlite3_stmt *DataBase::prepareStatement(const char *sql) {
  sqlite3_stmt *stmt;
  int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (exit != SQLITE_OK) {
    std::cerr << "Error while preparing statement: " << sqlite3_errmsg(db)
              << std::endl;
    return nullptr;
  }
  return stmt;
}

bool DataBase::processQuery(sqlite3_stmt *stmt, std::string msg) {
  int exit = sqlite3_step(stmt);

  if (exit != SQLITE_DONE) {
    std::cerr << "Error while processing query: " << sqlite3_errmsg(db)
              << std::endl;
    sqlite3_finalize(stmt);
    return false;
  } else
    std::cout << msg << std::endl;

  sqlite3_finalize(stmt);
  return true;
}

void DataBase::insertCircle(Circle c) {
  if (!openDb())
    return;

  std::vector<std::string> circlesNames;
  const char *sql = "SELECT name FROM CIRCLES;";

  sqlite3_stmt *stmt = prepareStatement(sql);
  if (!stmt) {
    closeDb();
    return;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *name = sqlite3_column_text(stmt, 0);
    if (name)
      circlesNames.push_back(std::string(reinterpret_cast<const char *>(name)));
  }
  sqlite3_finalize(stmt);

  if (std::find(circlesNames.begin(), circlesNames.end(), c.getName()) !=
      circlesNames.end()) {
    std::cout << "Circle already in DB" << std::endl;
    closeDb();
    return;
  }

  sql = R"(
        INSERT INTO CIRCLES (name, render, radius, mass, xPos, yPos, xVel, yVel, r, g, b)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

  stmt = prepareStatement(sql);
  if (!stmt) {
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

  processQuery(stmt, "Inserted Circle successfully!");
  closeDb();
}

void DataBase::deleteCircle(Circle c) {
  if (!openDb())
    return;

  const char *sql = "SELECT name FROM CIRCLES;";

  sqlite3_stmt *stmt = prepareStatement(sql);
  if (!stmt) {
    closeDb();
    return;
  }

  std::vector<std::string> circlesNames;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *name = sqlite3_column_text(stmt, 0);
    if (name)
      circlesNames.push_back(std::string(reinterpret_cast<const char *>(name)));
  }
  sqlite3_finalize(stmt);

  if (std::find(circlesNames.begin(), circlesNames.end(), c.getName()) ==
      circlesNames.end()) {
    std::cout << "Circle not in DB!" << std::endl;
    closeDb();
    return;
  }

  sql = "DELETE FROM CIRCLES WHERE name = ?;";

  stmt = prepareStatement(sql);
  if (!stmt) {
    closeDb();
    return;
  }

  sqlite3_bind_text(stmt, 1, c.getName().c_str(), -1, SQLITE_TRANSIENT);

  processQuery(stmt, "Deleted Circle successfully!");
  closeDb();
}

std::vector<Circle> DataBase::getAllCircles() {
  std::vector<Circle> circles;

  if (!openDb()) {
    std::cerr << "Can't open DB!" << sqlite3_errmsg(db) << std::endl;
    return {};
  }

  const char *sql = R"(
        SELECT name, render, radius, mass, xPos, yPos, xVel, yVel, r, g, b FROM CIRCLES;
    )";

  sqlite3_stmt *stmt = prepareStatement(sql);
  if (!stmt) {
    closeDb();
    std::cerr << "Can't prepare statement!" << sqlite3_errmsg(db);
    return {};
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::string name =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    bool render = sqlite3_column_int(stmt, 1);
    float radius = static_cast<float>(sqlite3_column_double(stmt, 2));
    float mass = static_cast<float>(sqlite3_column_double(stmt, 3));
    float xPos = static_cast<float>(sqlite3_column_double(stmt, 4));
    float yPos = static_cast<float>(sqlite3_column_double(stmt, 5));
    float xVel = static_cast<float>(sqlite3_column_double(stmt, 6));
    float yVel = static_cast<float>(sqlite3_column_double(stmt, 7));
    int r = sqlite3_column_int(stmt, 8);
    int g = sqlite3_column_int(stmt, 9);
    int b = sqlite3_column_int(stmt, 10);

    Circle c(name, render, radius, mass, xPos, yPos, xVel, yVel, r, g, b);
    circles.push_back(c);
  }

  sqlite3_finalize(stmt);
  closeDb();

  return circles;
}
