#include "ecs/core/Entity.h"
#include "ecs/systems/CheckEnemyDeathSystem.h"
#include "utils/Vec2.h"
#include <cmath>
#include <numbers>

constexpr float DEATH_FRAGMENT_SPEED = 2.f;
constexpr float DEATH_FRAGMENT_ROTATION_SPEED = 2.f;

void CheckEnemyDeathSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CLife>() || e->tag() != "Enemy")
      continue;

    if (e->get<CLife>().hp <= 0) {

      auto &shape = e->get<CShape>();
      auto &transform = e->get<CTransform>();

      int fragments = shape.points;
      Vec2 direction;
      float r = shape.radius;
      float step = 2.f * std::numbers::pi / fragments;

      for (auto i = 0; i < fragments; i++) {

        float angle = step * i;
        float speed =
            DEATH_FRAGMENT_SPEED * (0.5f + (rand() / (float)RAND_MAX));

        direction.x = r + r * std::cos(angle);
        direction.y = r + r * std::sin(angle);

        auto deathShadow = em.addEntity("DeathShadow");
        deathShadow->add<CShape>(shape.points, shape.radius - 10,
                                 shape.fillColor);
        deathShadow->add<CTransform>(transform.pos, direction * speed,
                                     direction * speed);
        deathShadow->add<CLifeSpan>(50);
        deathShadow->add<CRotation>(DEATH_FRAGMENT_ROTATION_SPEED);
      }

      e->destroy();
    }
  }
}
