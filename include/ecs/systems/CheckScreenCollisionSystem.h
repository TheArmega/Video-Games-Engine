#ifndef CHECKSCREENCOLLISIONSYSTEM_H
#define CHECKSCREENCOLLISIONSYSTEM_H

#include "core/Window.h"
#include "ecs/core/EntityManager.h"
class CheckScreenCollisionSystem {

public:
  void update(EntityManager &em, Window &w);
};

#endif // CHECKSCREENCOLLISIONSYSTEM_H
