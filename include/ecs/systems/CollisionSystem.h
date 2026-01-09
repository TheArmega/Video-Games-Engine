#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ecs/core/EntityManager.h"
class CollisionSystem {

public:
  void update(EntityManager &em);
};

#endif // COLLISIONSYSTEM
