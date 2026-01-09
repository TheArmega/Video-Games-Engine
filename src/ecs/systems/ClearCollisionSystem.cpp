#include "ecs/core/Entity.h"
#include "ecs/systems/ClearCollisionSystem.h"

void ClearCollisionSystem::update(EntityManager &em) {

  for (auto &e : em.getEntities()) {
    if (!e->has<CCollision>())
      continue;

    e->remove<CCollision>();
  }
}
