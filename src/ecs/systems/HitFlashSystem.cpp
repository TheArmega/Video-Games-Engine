#include "ecs/core/Entity.h"
#include "ecs/systems/HitFlashSystem.h"

void HitFlashSystem::update(EntityManager &em, float dt) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CHitFlash>() || !e->has<CShape>())
      continue;

    auto &hitFlash = e->get<CHitFlash>();
    auto &shape = e->get<CShape>();

    hitFlash.timer += dt;
    shape.shape.setFillColor(sf::Color::Yellow);

    if (hitFlash.timer >= hitFlash.duration) {
      shape.shape.setFillColor(shape.fillColor);
      e->remove<CHitFlash>();
    }
  }
}
