#include "ecs/core/Entity.h"
#include "ecs/systems/EnemyMovementSystem.h"
#include "utils/Vec2.h"
#include <cmath>

constexpr float ENEMY_SPEED = 100.f;

void EnemyMovementSystem::update(EntityManager &em, float dt) {

  auto players = em.getEntities("Player");
  if (players.empty())
    return;

  auto &playerTransform = players[0]->get<CTransform>();

  for (auto &e : em.getEntities()) {
    if (e->tag() != "Enemy")
      continue;

    auto &transform = e->get<CTransform>();
    auto &wobble = e->get<CWobble>();

    wobble.phase += dt * wobble.frequency;
    float offset = std::sin(wobble.phase) * wobble.amplitude;

    Vec2 v = playerTransform.pos - transform.pos;
    float n = v.module();
    Vec2 dir = v / n;
    Vec2 perp(-dir.y, dir.x);

    float wobbleStrength = 0.2f; // controla intensidad lateral
    Vec2 finalDir = (dir + perp * offset * wobbleStrength).normalized();

    transform.velocity = finalDir * ENEMY_SPEED;
  }
}
