add_library(UILib STATIC
    Button.cpp
    Title.cpp
)

target_include_directories(UILib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
