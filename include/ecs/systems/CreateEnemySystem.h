#ifndef CREATEENEMYSYSTEM_H
#define CREATEENEMYSYSTEM_H

#include "ecs/core/EntityManager.h"
class CreateEnemySystem {
public:
  std::shared_ptr<Entity> create(EntityManager &em);
};

#endif // CREATEENEMYSYSTEM_H
