#include "scenes/SceneManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <memory>

SceneManager::~SceneManager() {
  if (currentScene) {
    currentScene->cleanUp();
  }
}

void SceneManager::setScene(std::unique_ptr<Scene> scene) {
  if (currentScene) {
    currentScene->cleanUp();
  }

  currentScene = std::move(scene);

  if (currentScene) {
    currentScene->init();
  }
}

void SceneManager::update(float deltaTime) {
  if (currentScene) {
    currentScene->update(deltaTime);
  }
}

void SceneManager::render(sf::RenderWindow &window) {
  if (currentScene) {
    currentScene->render(window);
  }
}
