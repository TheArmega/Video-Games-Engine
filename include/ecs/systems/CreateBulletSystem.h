#ifndef CREATEBULLETSYSTEM_H
#define CREATEBULLETSYSTEM_H

#include "ecs/core/EntityManager.h"
#include <memory>
class CreateBulletSystem {

public:
  std::shared_ptr<Entity> create(EntityManager &em);
};

#endif // CREATEBULLETSYSTEM_H
