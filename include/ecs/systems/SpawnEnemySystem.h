#ifndef SPAWNENEMYSYSTEM_H
#define SPAWNENEMYSYSTEM_H

#include "core/Window.h"
#include "ecs/core/EntityManager.h"
class SpawnEnemySystem {

public:
  void spawn(EntityManager &em, Window &w);
};

#endif /// SPAWNENEMYSYSTEM_H
