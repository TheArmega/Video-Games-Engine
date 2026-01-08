#include "ecs/core/Entity.h"
#include "ecs/systems/CreateEnemySystem.h"
#include <memory>

std::shared_ptr<Entity> CreateEnemySystem::create(EntityManager &em) {
  auto enemy = em.addEntity("Enemy");
  enemy->add<CShape>(3, 10, sf::Color::Red);
  enemy->add<CTransform>();
  enemy->add<CLife>();

  return enemy;
}
