/**
 * @file dataBase.h
 * @author Jaime
 * @brief DataBase class declaration
 * @version 0.1
 * @date 23/10/25
 *
 * @defgroup DataBaseModule DataBase Class
 * @brief Manages SQLite database operations for Circle objects
 * @{
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <algorithm>
#include <iostream>
#include <sqlite3.h>
#include <vector>

#include "circle.h"

/// @brief This const storage the main structure of the bd circles table.
extern const std::string TABLE_CREATION_QUERY;

/**
 * @class DataBase
 * @brief Handles SQLite database operations for Circle objects.
 *
 * This class allows creating a database, creating tables, inserting,
 * deleting, and retrieving Circle objects, using SQLite3.
 */
class DataBase {
private:
  sqlite3 *db = nullptr; ///< SQLite database pointer
  std::string dbFile;    ///< Path to the database file

public:
  /**
   * @brief Constructs a new DataBase object
   * @param _dbFile Path to the database file
   */
  DataBase(const std::string _dbFile);

  /**
   * @brief Destructs the DataBase object and closes the connection
   */
  ~DataBase();

  // =======================
  // Delete copy
  // =======================
  DataBase(const DataBase &) = delete;
  DataBase &operator=(const DataBase &) = delete;

  // =======================
  // Move semantics
  // =======================
  DataBase(DataBase &&other) noexcept;
  DataBase &operator=(DataBase &&other) noexcept;

  /// @name Setters
  /// @{
  void setDbFile(std::string f); ///< Sets the database file path
  /// @}

  /// @name Getters
  /// @{
  std::string getDbFile(); ///< Returns the database file path
  /// @}

  /// @name Methods
  /// @{
  /**
   * @brief Opens the database connection
   * @return True if opened successfully
   */
  bool openDb();

  /**
   * @brief Closes the database connection
   */
  void closeDb();

  /**
   * @brief Checks if the database exists and is accessible
   * @param f Database file path
   */
  void checkDbExist(std::string f);

  /**
   * @brief Creates the CIRCLES table if it does not exist
   * @param t SQL table creation query (default TABLE_CREATION_QUERY)
   */
  void createTable(std::string t = TABLE_CREATION_QUERY);

  /**
   * @brief Prepares a SQLite statement
   * @param sql SQL query string	Constructs a new CircleContainer object.

Setters
   * @return Pointer to prepared statement
   */
  sqlite3_stmt *prepareStatement(const char *sql);

  /**
   * @brief Executes a prepared statement
   * @param stmt Prepared SQLite statement
   * @param msg Message to print on success
   * @return True if query executed successfully
   */
  bool processQuery(sqlite3_stmt *stmt, std::string msg);

  /**
   * @brief Inserts a Circle into the database
   * @param circle Circle object to insert
   */
  void insertCircle(Circle circle);

  /**
   * @brief Deletes a Circle from the database
   * @param circle Circle object to delete
   */
  void deleteCircle(Circle circle);

  /**
   * @brief Retrieves all Circles from the database
   * @return Vector of Circle objects
   */
  std::vector<Circle> getAllCircles();
  /// @}
};

#endif // DATABASE_H

/** @} */ // end of DataBaseModule
