#include "ecs/core/Entity.h"
#include "ecs/systems/ShapeRotationSystem.h"
#include <SFML/System/Angle.hpp>

void ShapeRotationSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CShape>() || !e->has<CRotation>())
      continue;

    auto &shape = e->get<CShape>();
    auto &rotationSpeed = e->get<CRotation>();
    shape.shape.rotate(rotationSpeed.velocity);
  }
}
