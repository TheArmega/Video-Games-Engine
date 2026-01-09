#ifndef BULLETDAMAGESYSTEM_H
#define BULLETDAMAGESYSTEM_H

#include "ecs/core/EntityManager.h"
class BulletDamageSystem {

public:
  void update(EntityManager &em);
};

#endif // BULLETDAMAGESYSTEM
