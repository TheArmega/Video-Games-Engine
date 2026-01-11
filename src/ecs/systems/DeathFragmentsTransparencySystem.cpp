#include "ecs/core/Entity.h"
#include "ecs/systems/DeathFragmentsTransparencySystem.h"

void DeathFragmentsTransparencySystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (e->tag() != "DeathShadow" || !e->has<CLifeSpan>())
      continue;

    auto &shape = e->get<CShape>();
    auto &lifeSpan = e->get<CLifeSpan>().life;
    shape.fillColor.a = lifeSpan;
    shape.outLineColor.a = lifeSpan;
    shape.shape.setFillColor(shape.fillColor);
    shape.shape.setOutlineColor(shape.outLineColor);
  }
}
