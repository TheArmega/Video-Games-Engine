#include "ecs/systems/CheckScreenCollisionSystem.h"

constexpr float BORDER = 25.f;

void CheckScreenCollisionSystem::update(EntityManager &em, Window &w) {
  for (auto &e : em.getEntities()) {

    if (e->tag() != "Player")
      continue;

    auto &shape = e->get<CShape>();
    auto &transform = e->get<CTransform>();
    Vec2 pos = transform.pos;

    auto width = w.getWidth();
    auto height = w.getHeight();

    float xR = pos.x + shape.radius;
    float xL = pos.x - shape.radius;
    float yU = pos.y + shape.radius;
    float yD = pos.y - shape.radius;

    if (xL - BORDER <= 0)
      transform.pos.x = shape.radius + BORDER;
    if (xR + BORDER >= width)
      transform.pos.x = width - shape.radius - BORDER;
    if (yD - BORDER <= 0)
      transform.pos.y = shape.radius + BORDER;
    if (yU + BORDER >= height)
      transform.pos.y = height - shape.radius - BORDER;
  }
}
