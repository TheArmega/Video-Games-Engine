#include "ecs/core/Entity.h"
#include "ecs/systems/CreateEnemySystem.h"
#include "ecs/systems/SpawnEnemySystem.h"
#include "utils/Geometry.h"

void SpawnEnemySystem::spawn(EntityManager &em, Window &w) {

  CreateEnemySystem createEnemySystem;
  auto enemy = createEnemySystem.create(em);
  auto &transform = enemy->get<CTransform>();

  constexpr int MAX_TRIES = 100;
  Vec2 spawnPos;
  bool found = false;

  for (int i = 0; i < MAX_TRIES; ++i) {

    Vec2 p = {float(rand() % w.getWidth()), float(rand() % w.getHeight())};

    bool valid = true;

    for (auto &e : em.getEntities()) {
      if (!e->has<CTransform>() || !e->has<CShape>())
        continue;

      auto &transform = e->get<CTransform>();
      auto &shape = e->get<CShape>();

      if (Geometry::pointInCircle(p, transform.pos, shape.radius)) {
        valid = false;
        break;
      }
    }

    if (valid) {
      spawnPos = p;
      found = true;
      break;
    }
    break;
  }

  if (!found)
    return;

  transform.pos = spawnPos;
}
