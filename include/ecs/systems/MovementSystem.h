#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ecs/core/EntityManager.h"

class MovementSystem {
public:
  void update(EntityManager &em, float dt);
};

#endif // MOVEMENTSYSTEM_H
