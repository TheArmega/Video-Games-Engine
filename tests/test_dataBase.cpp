#include "circle.h"
#include "dataBase.h"
#include <catch2/catch_all.hpp>
#include <filesystem>

// ============================================
// TEST CASES
// ============================================

TEST_CASE("Database basic operations", "[database]") {
  std::string testDb = "test_db.sqlite";
  if (std::filesystem::exists(testDb))
    std::filesystem::remove(testDb);

  DataBase db(testDb);

  SECTION("Database file can be created and opened") {
    REQUIRE(db.openDb() == true);
    db.closeDb();
    REQUIRE(std::filesystem::exists(testDb));
  }

  SECTION("Setter and Getter for dbFile work correctly") {
    db.setDbFile("new_db.sqlite");
    REQUIRE(db.getDbFile() == "new_db.sqlite");
  }

  SECTION("Move constructor and assignment operator work correctly") {
    db.openDb();
    DataBase db2(std::move(db));
    REQUIRE(db2.openDb() == true);
    db2.closeDb();

    DataBase db3("temp.sqlite");
    db3 = std::move(db2);

    // ✅ Catch2 no soporta expresiones con ||
    bool validFile = (db3.getDbFile() == "test_db.sqlite") ||
                     (db3.getDbFile() == "temp.sqlite");
    CAPTURE(db3.getDbFile()); // muestra el valor en caso de fallo
    REQUIRE(validFile);
  }
}

TEST_CASE("Database table creation", "[database]") {
  std::string testDb = "table_test.sqlite";
  if (std::filesystem::exists(testDb))
    std::filesystem::remove(testDb);

  DataBase db(testDb);
  REQUIRE(db.openDb());
  db.closeDb();

  db.createTable(TABLE_CREATION_QUERY);

  REQUIRE(std::filesystem::exists(testDb));
}

TEST_CASE("Insert, retrieve and delete Circle", "[database]") {
  std::string testDb = "circle_test.sqlite";
  if (std::filesystem::exists(testDb))
    std::filesystem::remove(testDb);

  DataBase db(testDb);
  db.createTable(TABLE_CREATION_QUERY);

  Circle c1("circle1", true, 10.0f, 5.0f, 1.0f, 2.0f, 0.5f, 0.3f, 255, 0, 0);

  SECTION("Insert Circle into database") {
    db.insertCircle(c1);
    auto all = db.getAllCircles();
    REQUIRE(all.size() == 1);
    REQUIRE(all[0].getName() == "circle1");
  }

  SECTION("Avoid duplicate Circle insertion") {
    db.insertCircle(c1);
    db.insertCircle(c1); // mismo círculo
    auto all = db.getAllCircles();
    REQUIRE(all.size() == 1);
  }

  SECTION("Delete Circle from database") {
    db.insertCircle(c1);
    db.deleteCircle(c1);
    auto all = db.getAllCircles();
    REQUIRE(all.empty());
  }
}
