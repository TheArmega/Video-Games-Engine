#include "ecs/core/Entity.h"
#include "ecs/systems/EnemyDamageSystem.h"

void EnemyDamageSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (e->tag() != "Enemy" || !e->has<CCollision>())
      continue;

    auto &otherId = e->get<CCollision>().otherId;
    auto other = em.getEntityById(otherId);

    if (other->tag() != "Player")
      continue;

    other->get<CLife>().hp -= e->get<CDamage>().damage;

    e->destroy();
  }
}
