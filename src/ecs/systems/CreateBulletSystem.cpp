#include "ecs/systems/CreateBulletSystem.h"
#include <SFML/Graphics/Color.hpp>
#include <memory>

std::shared_ptr<Entity> CreateBulletSystem::create(EntityManager &em) {

  auto bullet = em.addEntity("Bullet");
  bullet->add<CShape>(10, sf::Color::White);
  bullet->add<CTransform>();
  bullet->add<CLifeSpan>();

  return bullet;
}
