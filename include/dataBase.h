#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

#include <iostream>

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
  void checkDbExist(std::string f);
  void createTable(std::string t = TABLE_CREATION_QUERY);
};

#endif // DATABASE_H
