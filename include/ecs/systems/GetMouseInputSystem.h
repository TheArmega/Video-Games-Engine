#ifndef GETMOUSEINPUTSYSTEM_H
#define GETMOUSEINPUTSYSTEM_H

#include "ecs/core/EntityManager.h"
class GetMouseInputSystem {

public:
  void update(EntityManager &em, const sf::Event &event);
};

#endif // GETMOUSEINPUTSYSTEM_H
