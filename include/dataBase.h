#ifndef DATABASE_H
#define DATABASE_H

#include <algorithm>
#include <iostream>
#include <sqlite3.h>

#include "circle.h"

extern const std::string TABLE_CREATION_QUERY;

class DataBase {
private:
  sqlite3 *db;
  std::string dbFile;

public:
  DataBase(const std::string _dbFile);

  // Setters
  void setDbFile(std::string f);

  // Getters
  std::string getDbFile();

  // Mehods
  bool openDb();
  void closeDb();
  void checkDbExist(std::string f);
  void createTable(std::string t = TABLE_CREATION_QUERY);
  sqlite3_stmt *prepareStatement(const char *sql);
  bool processQuery(sqlite3_stmt *stmt, std::string msg);
  void insertCircle(Circle circle);
  void deleteCircle(Circle circle);
  std::vector<Circle> getAllCircles();
};

#endif // DATABASE_H
