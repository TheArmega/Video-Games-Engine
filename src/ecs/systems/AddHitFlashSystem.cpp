#include "ecs/systems/AddHitFlashSystem.h"

void AddHitFlashSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CCollision>() || !e->has<CLife>())
      continue;

    auto &otherId = e->get<CCollision>().otherId;
    auto other = em.getEntityById(otherId);

    if (other->tag() == e->tag())
      continue;

    e->add<CHitFlash>();
  }
}
