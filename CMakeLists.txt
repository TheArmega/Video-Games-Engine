cmake_minimum_required(VERSION 3.15)
project(VideoGamesEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Buscar SFML 3
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

# Definir rutas de librerías externas
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui")
set(IMGUI_SFML_DIR "${CMAKE_SOURCE_DIR}/imgui-sfml")

add_executable(VideoGamesEngine
  src/main.cpp
<<<<<<< Updated upstream
=======
  src/circle.cpp
  src/circleContainer.cpp
>>>>>>> Stashed changes
)

# Agregar subdirectorio de ImGui-SFML
add_subdirectory(${IMGUI_SFML_DIR})

# Incluir headers propios y de ImGui-SFML
target_include_directories(VideoGamesEngine
    PRIVATE
    include
    ${IMGUI_DIR}
    ${IMGUI_SFML_DIR}
)

target_link_libraries(VideoGamesEngine
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    ImGui-SFML
)
