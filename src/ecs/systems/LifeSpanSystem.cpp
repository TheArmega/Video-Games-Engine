#include "ecs/core/Entity.h"
#include "ecs/systems/LifeSpanSystem.h"

void LifeSpanSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CLifeSpan>())
      continue;

    auto &lifeSpan = e->get<CLifeSpan>();
    lifeSpan.life -= 1;

    if (lifeSpan.life == 0)
      e->destroy();
  }
}
