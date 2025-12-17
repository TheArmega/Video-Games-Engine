add_library(ScenesLib STATIC
    Scene.cpp
    SceneManager.cpp
    TitleScene.cpp
)

target_include_directories(ScenesLib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ScenesLib
    PUBLIC
        CoreLib
        ImGui-SFML::ImGui-SFML
)
