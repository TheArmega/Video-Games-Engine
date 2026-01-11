#ifndef HITFLASHSYSTEM_H
#define HITFLASHSYSTEM_H

#include "ecs/core/EntityManager.h"
class HitFlashSystem {

public:
  void update(EntityManager &em, float dt);
};

#endif // HITFLASHSYSTEM_H
