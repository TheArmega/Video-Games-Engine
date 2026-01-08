#ifndef LIFESPANSYSTEM_H
#define LIFESPANSYSTEM_H

#include "ecs/core/EntityManager.h"

class LifeSpanSystem {
public:
  void update(EntityManager &em);
};

#endif // LIFESPANSYSTEM_H
