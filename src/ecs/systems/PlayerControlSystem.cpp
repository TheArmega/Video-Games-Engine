#include "ecs/core/Entity.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/PlayerControlSystem.h"

void PlayerControlSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (e->has<CInput>() && e->has<CTransform>()) {
      auto &input = e->get<CInput>();
      auto &transform = e->get<CTransform>();

      if (input.up && !input.down)
        transform.velocity.y = -transform.speed.y;
      else if (!input.up && input.down)
        transform.velocity.y = transform.speed.y;
      else
        transform.velocity.y = 0;

      if (input.left && !input.right)
        transform.velocity.x = -transform.speed.x;
      else if (!input.left && input.right)
        transform.velocity.x = transform.speed.x;
      else
        transform.velocity.x = 0;
    };
  };
}
