#include "ecs/core/Entity.h"
#include "ecs/systems/BulletDamageSystem.h"

constexpr float SCORE_POINTS = 10;

void BulletDamageSystem::update(EntityManager &em) {

  for (auto &e : em.getEntities()) {

    if (e->tag() != "Bullet" || !e->has<CCollision>() || !e->has<CDamage>())
      continue;

    auto &otherId = e->get<CCollision>().otherId;
    auto other = em.getEntityById(otherId);

    auto playerId = e->get<COwner>().owner;
    auto player = em.getEntityById(playerId);
    auto &score = player->get<CScore>();

    if (!other || !other->has<CLife>() || other->tag() == "Player") {
      continue;
    }

    other->get<CLife>().hp -= e->get<CDamage>().damage;
    if (other->get<CLife>().hp <= 0)
      score.score += SCORE_POINTS;

    e->destroy();
  }
}
