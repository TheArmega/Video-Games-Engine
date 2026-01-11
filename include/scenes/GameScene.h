#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "core/Window.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/AddHitFlashSystem.h"
#include "ecs/systems/BulletDamageSystem.h"
#include "ecs/systems/CheckDeathSystem.h"
#include "ecs/systems/CheckEnemyDeathSystem.h"
#include "ecs/systems/CheckScreenCollisionSystem.h"
#include "ecs/systems/ClearCollisionSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/DeathFragmentsTransparencySystem.h"
#include "ecs/systems/DisplayScoreSystem.h"
#include "ecs/systems/EnemyDamageSystem.h"
#include "ecs/systems/EnemyMovementSystem.h"
#include "ecs/systems/GetKeyboardInputSystem.h"
#include "ecs/systems/GetMouseInputSystem.h"
#include "ecs/systems/HitFlashSystem.h"
#include "ecs/systems/LifeSpanSystem.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/PlayerControlSystem.h"
#include "ecs/systems/PlayerShootSystem.h"
#include "ecs/systems/ShapeRotationSystem.h"
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
  CollisionSystem collisionSystem;
  ClearCollisionSystem clearCollisionSystem;
  BulletDamageSystem bulletDamageSystem;
  CheckDeathSystem checkDeathSystem;
  EnemyDamageSystem enemyDamageSystem;
  AddHitFlashSystem addHitFlashSystem;
  HitFlashSystem hitFlashSystem;
  ShapeRotationSystem shapeRotationSystem;
  CheckEnemyDeathSystem checkEnemyDeathSystem;
  DeathFragmentsTransparencySystem deathFragmentsTransparencySystem;
  CheckScreenCollisionSystem checkScreenCollisionSystem;
  DisplayScoreSystem displayScoreSystem;

public:
  explicit GameScene(Window *w, EntityManager *em);

  void init() override;
  void update(float dt) override;
  void render() override;
  void cleanUp() override;
  void handleEvent(const sf::Event &event) override;
};

#endif // GAMESCENE_H
