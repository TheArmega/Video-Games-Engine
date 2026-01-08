#include "ecs/core/Entity.h"
#include "ecs/systems/EnemyMovementSystem.h"
#include "utils/Vec2.h"
#include <cmath>

constexpr float ENEMY_SPEED = 100.f;

void EnemyMovementSystem::update(EntityManager &em) {

  auto players = em.getEntities("Player");

  if (players.empty())
    return;

  auto &playerTransform = players[0]->get<CTransform>();

  for (auto &e : em.getEntities()) {

    if (e->tag() != "Enemy") {
      continue;
    }

    auto &transform = e->get<CTransform>();

    Vec2 v = playerTransform.pos - transform.pos;
    float n = std::sqrt(v.x * v.x + v.y * v.y);

    Vec2 dir = v / n;
    transform.velocity = dir * ENEMY_SPEED;
  }
}
