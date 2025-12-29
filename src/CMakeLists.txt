# Subdirectorios con código fuente
add_subdirectory(core)
add_subdirectory(ecs)
add_subdirectory(utils)
add_subdirectory(ui)
add_subdirectory(scenes)

# Ruta a ImGui
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui" CACHE PATH "Path to ImGui top-level directory")

# Añadir ImGui-SFML con directorio de build separado
add_subdirectory(${CMAKE_SOURCE_DIR}/external/imgui-sfml ${CMAKE_BINARY_DIR}/imgui-sfml-build)

# Ejecutable principal
add_executable(Game main.cpp)

# Enlazar librerías
target_link_libraries(Game
    PRIVATE
        CoreLib
        UILib
        ImGui-SFML
)

# Incluir cabeceras globales
target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Enlazar librerías del motor
target_link_libraries(Game PRIVATE CoreLib ScenesLib UILib)
