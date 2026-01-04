#include "core/Engine.h"
#include "ecs/core/Entity.h"
#include "ecs/core/EntityManager.h"
#include "imgui-SFML.h"
#include "scenes/GameScene.h"
#include "utils/Vec2.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GameScene::GameScene(Window *w, EntityManager *em)
    : Scene("Game Scene", em), window(w) {};

void GameScene::init() {
  auto player = entityManager->addEntity("Player");
  player->add<CTransform>(Vec2(0, 0), Vec2(0, 0));
  player->add<CShape>();
  return;
}

void GameScene::update() {
  // Update Scene
  return;
}

void GameScene::render(sf::RenderWindow &w) {
  for (auto &e : entityManager->getEntities()) {
    if (e->has<CTransform>() && e->has<CShape>()) {
      auto &transform = e->get<CTransform>();
      auto &shape = e->get<CShape>();

      shape.shape.setPosition({transform.pos.x, transform.pos.y});
      shape.shape.setRadius(100);
      shape.shape.setFillColor(sf::Color::Red);
      w.draw(shape.shape);
    }
  }

  return;
}

void GameScene::cleanUp() { return; }

void GameScene::handleEvent(const sf::Event &event) { return; }
