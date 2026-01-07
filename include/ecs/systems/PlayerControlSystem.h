#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "ecs/core/EntityManager.h"
class PlayerControlSystem {
public:
  void update(EntityManager &em);
};

#endif // PLAYERCONTROLSYSTEM
