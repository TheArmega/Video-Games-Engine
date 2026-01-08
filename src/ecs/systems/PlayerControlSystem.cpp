#include "ecs/core/Entity.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/PlayerControlSystem.h"

void PlayerControlSystem::update(EntityManager &em) {
  for (auto &e : em.getEntities()) {
    if (e->has<CInput>() && e->has<CTransform>()) {
      auto &input = e->get<CInput>();
      auto &transform = e->get<CTransform>();

      if (input.up && !input.down)
        transform.velocity.y = -transform.maxVelocity.y;
      else if (!input.up && input.down)
        transform.velocity.y = transform.maxVelocity.y;
      else
        transform.velocity.y = 0;

      if (input.left && !input.right)
        transform.velocity.x = -transform.maxVelocity.x;
      else if (!input.left && input.right)
        transform.velocity.x = transform.maxVelocity.x;
      else
        transform.velocity.x = 0;

      if ((input.left && input.up) || (input.left && input.down) ||
          (input.right && input.up) || (input.right && input.down)) {
        transform.velocity.x /= 2;
        transform.velocity.y /= 2;
      }
    };
  };
}
