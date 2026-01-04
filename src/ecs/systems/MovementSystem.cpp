#include "ecs/core/Entity.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/MovementSystem.h"

void MovementSystem::update(EntityManager &em, float dt) {
  for (auto e : em.getEntities()) {
    if (e->has<CTransform>()) {
      auto &transform = e->get<CTransform>();
      transform.pos.add(transform.velocity * dt);
    }
  }
}
