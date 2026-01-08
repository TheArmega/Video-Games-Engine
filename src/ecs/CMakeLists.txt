add_library(ECSLib)
add_subdirectory(core)
add_subdirectory(systems)

target_include_directories(ECSLib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ECSLib PRIVATE CoreLib)


