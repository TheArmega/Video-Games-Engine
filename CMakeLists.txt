cmake_minimum_required(VERSION 3.15)
project(VideoGameEngine VERSION 1.0 LANGUAGES CXX)

# Estándar C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Carpeta de build independiente
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Esto es para Helix
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Añadir subdirectorio src
add_subdirectory(src)
