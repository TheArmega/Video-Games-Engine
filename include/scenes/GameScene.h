#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "core/Window.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/EnemyMovementSystem.h"
#include "ecs/systems/GetKeyboardInputSystem.h"
#include "ecs/systems/GetMouseInputSystem.h"
#include "ecs/systems/LifeSpanSystem.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/PlayerControlSystem.h"
#include "ecs/systems/PlayerShootSystem.h"
#include "ecs/systems/SpawnEnemySystem.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class GameScene : public Scene {
private:
  Window *window;
  MovementSystem movementSystem;
  GetKeyboardInputSystem getKeyboardInputSystem;
  GetMouseInputSystem getMouseInputSystem;
  PlayerControlSystem playerControlSystem;
  PlayerShootSystem playerShootSystem;
  SpawnEnemySystem spawnEnemySystem;
  EnemyMovementSystem enemyMovementSystem;
  LifeSpanSystem lifeSpanSystem;

public:
  explicit GameScene(Window *w, EntityManager *em);

  void init() override;
  void update(float dt) override;
  void render() override;
  void cleanUp() override;
  void handleEvent(const sf::Event &event) override;
};

#endif // GAMESCENE_H
