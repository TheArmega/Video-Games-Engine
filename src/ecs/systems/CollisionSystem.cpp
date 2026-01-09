#include "ecs/core/Entity.h"
#include "ecs/systems/CollisionSystem.h"

void CollisionSystem::update(EntityManager &em) {
  auto &entities = em.getEntities();

  for (auto &a : entities) {

    if (!a->has<CTransform>() || !a->has<CShape>())
      continue;

    for (auto &b : entities) {

      if (!b->has<CTransform>() || !b->has<CShape>() || b == a)
        continue;

      if (a->get<CShape>().shape.getGlobalBounds().findIntersection(
              b->get<CShape>().shape.getGlobalBounds())) {
        a->add<CCollision>(b->id());
        b->add<CCollision>(a->id());
      }
    }
  }
}
