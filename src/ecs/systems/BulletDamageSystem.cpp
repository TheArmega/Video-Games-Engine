#include "ecs/core/Entity.h"
#include "ecs/systems/BulletDamageSystem.h"

void BulletDamageSystem::update(EntityManager &em) {

  for (auto &e : em.getEntities()) {

    if (e->tag() != "Bullet" || !e->has<CCollision>() || !e->has<CDamage>())
      continue;

    auto &otherId = e->get<CCollision>().otherId;
    auto other = em.getEntityById(otherId);

    if (!other || !other->has<CLife>() || other->tag() == "Player") {
      continue;
    }

    other->get<CLife>().hp -= e->get<CDamage>().damage;
    e->destroy();
  }
}
