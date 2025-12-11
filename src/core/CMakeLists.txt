# Crear librería del core
add_library(CoreLib Engine.cpp)

# Incluir cabeceras del core
target_include_directories(CoreLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
