#include "scenes/SceneCommand.h"
#include "scenes/SceneManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
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

void SceneManager::update() {
  if (currentScene) {
    currentScene->update();
  }
}

void SceneManager::render(sf::RenderWindow &window) {
  if (currentScene) {
    currentScene->render(window);
  }
}

void SceneManager::eventHandler(const sf::Event &event) {
  if (currentScene) {
    currentScene->handleEvent(event);
  }
}

SceneCommand SceneManager::getActiveCommand() const {
  if (currentScene)
    return currentScene->getCommand();
  return SceneCommand::None;
}

void SceneManager::clearActiveCommand() {
  if (currentScene)
    currentScene->clearCommand();
}
