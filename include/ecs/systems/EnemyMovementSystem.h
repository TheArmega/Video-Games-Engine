#ifndef ENEMYMOVEMENTSYSTEM_H
#define ENEMYMOVEMENTSYSTEM_H

#include "ecs/core/EntityManager.h"
class EnemyMovementSystem {

public:
  void update(EntityManager &em, float dt);
};

#endif // ENEMYMOVEMENTSYSTEM_H
