#include "ecs/core/Entity.h"
#include "ecs/systems/CreateEnemySystem.h"
#include <memory>

std::shared_ptr<Entity> CreateEnemySystem::create(EntityManager &em) {
  auto enemy = em.addEntity("Enemy");
  enemy->add<CShape>(4, 20, sf::Color::Red);
  enemy->add<CTransform>();
  enemy->add<CLife>(50);
  enemy->add<CDamage>(10);
  enemy->add<CWobble>();

  return enemy;
}
