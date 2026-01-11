#ifndef DISPLAYSCORESYSTEM
#define DISPLAYSCORESYSTEM

#include "core/Window.h"
#include "ecs/core/EntityManager.h"

class DisplayScoreSystem {

public:
  void update(EntityManager &em, Window &w);
};

#endif // DISPLAYSCORESYSTEM
