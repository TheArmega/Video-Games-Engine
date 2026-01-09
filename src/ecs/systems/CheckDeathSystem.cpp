#include "ecs/core/Entity.h"
#include "ecs/systems/CheckDeathSystem.h"

void CheckDeathSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CLife>())
      continue;

    if (e->get<CLife>().hp <= 0)
      e->destroy();
  }
}
