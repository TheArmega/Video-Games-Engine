#include "imgui-SFML.h"
#include "scenes/GameScene.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GameScene::GameScene(Window *w) : Scene("Game Scene"), window(w) {};

void GameScene::init() { return; }

void GameScene::update() {
  // Update Scene
  return;
}

void GameScene::render(sf::RenderWindow &w) { return; }

void GameScene::cleanUp() { return; }

void GameScene::handleEvent(const sf::Event &event) { return; }
