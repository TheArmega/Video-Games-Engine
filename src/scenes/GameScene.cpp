#include "ecs/core/Entity.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/PlayerShootSystem.h"
#include "imgui-SFML.h"
#include "scenes/GameScene.h"
#include "utils/Vec2.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

static float acumulator = 0.f;
constexpr float ENEMY_SPAWN_STEP = 5.f;

GameScene::GameScene(Window *w, EntityManager *em)
    : Scene("Game Scene", em), window(w) {};

void GameScene::init() {

  auto player = entityManager->addEntity("Player");
  player->add<CShape>(30, 50, sf::Color::Green);
  player->add<CTransform>(
      Vec2(window->getWidth() / 2.f - player->get<CShape>().shape.getRadius(),
           window->getHeight() / 2.f - player->get<CShape>().shape.getRadius()),
      Vec2(0, 0), Vec2(500, 500));
  player->add<CLife>(200);
  player->add<CInput>();
}

void GameScene::update(float dt) {

  acumulator += dt;

  enemyMovementSystem.update(*entityManager);

  movementSystem.update(*entityManager, dt);
  lifeSpanSystem.update(*entityManager);

  if (acumulator >= ENEMY_SPAWN_STEP) {
    spawnEnemySystem.spawn(*entityManager, *window);
    acumulator -= ENEMY_SPAWN_STEP;
  }
}

void GameScene::render() {
  for (auto &e : entityManager->getEntities()) {
    if (e->has<CTransform>() && e->has<CShape>()) {
      auto &transform = e->get<CTransform>();
      e->get<CShape>().shape.setPosition({transform.pos.x, transform.pos.y});

      window->draw(e->get<CShape>().shape);
    }
  }
}

void GameScene::cleanUp() { return; }

void GameScene::handleEvent(const sf::Event &event) {
  getKeyboardInputSystem.update(*entityManager, event);
  playerControlSystem.update(*entityManager);
  getMouseInputSystem.update(*entityManager, event);
  playerShootSystem.update(*entityManager, window->getSfWindow());
}
