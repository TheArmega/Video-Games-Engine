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
  player->add<CSprite>("../assets/sprites/entities/characters/Pelota.png");
  player->add<CTransform>(Vec2(200, 700), Vec2(100, 100));

  auto circle = entityManager->addEntity("Circle");
  circle->add<CShape>();
  circle->add<CTransform>(Vec2(0, 0), Vec2(10, 10));
}

void GameScene::update(float dt) { movementSystem.update(*entityManager, dt); }

void GameScene::render() {
  for (auto &e : entityManager->getEntities()) {
    if (e->has<CTransform>() && e->has<CSprite>()) {

      auto &transform = e->get<CTransform>();
      auto &sprite = e->get<CSprite>();

      sprite.sprite.setPosition({transform.pos.x, transform.pos.y});
      sprite.sprite.setScale({8, 8});
      sprite.sprite.setTexture(sprite.texture);

      window->draw(sprite.sprite);
    }

    if (e->has<CTransform>() && e->has<CShape>()) {
      auto &transform = e->get<CTransform>();
      auto &shape = e->get<CShape>();
      shape.shape.setPosition({transform.pos.x, transform.pos.y});
      shape.shape.setFillColor(sf::Color::Red);
      shape.shape.setRadius(10.f);

      window->draw(shape.shape);
    }
  }
}

void GameScene::cleanUp() { return; }

void GameScene::handleEvent(const sf::Event &event) { return; }
