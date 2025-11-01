cmake_minimum_required(VERSION 3.15)
project(VideoGamesEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# =======================
# DEPENDENCIAS PRINCIPALES
# =======================

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)
find_package(SQLite3 REQUIRED)

# Rutas librerías externas
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui")
set(IMGUI_SFML_DIR "${CMAKE_SOURCE_DIR}/imgui-sfml")

# Desactivar ejemplos y tests de ImGui-SFML
set(IMGUI_SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(IMGUI_SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${IMGUI_SFML_DIR})

# =======================
# LIBRERÍA DEL MOTOR
# =======================

add_library(VideoGamesEngineLib
  src/circle.cpp
  src/circleContainer.cpp
  src/dataBase.cpp
  src/physicsEngine.cpp
)

target_include_directories(VideoGamesEngineLib
    PUBLIC include
    PUBLIC ${IMGUI_DIR}        # necesario para ImGui
    PUBLIC ${IMGUI_SFML_DIR}   # necesario para ImGui-SFML
)

target_link_libraries(VideoGamesEngineLib
    PUBLIC SFML::Graphics
    PUBLIC SFML::Window
    PUBLIC SFML::System
    PUBLIC SFML::Audio
    PUBLIC ImGui-SFML
    PUBLIC SQLite::SQLite3
)

# =======================
# EJECUTABLE PRINCIPAL
# =======================

add_executable(VideoGamesEngine src/main.cpp)
target_link_libraries(VideoGamesEngine PRIVATE VideoGamesEngineLib)

# =======================
# SECCIÓN DE TESTS
# =======================

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(catch2)

add_executable(VideoGamesEngineTests
  tests/test_circleContainer.cpp
  tests/test_dataBase.cpp
)

target_include_directories(VideoGamesEngineTests PRIVATE include)

target_link_libraries(VideoGamesEngineTests
  PRIVATE
  VideoGamesEngineLib       # enlaza tu código real
  Catch2::Catch2WithMain    # Catch2 proporciona main()
)

# Registrar tests con CTest
include(Catch)
catch_discover_tests(VideoGamesEngineTests)
