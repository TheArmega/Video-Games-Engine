#ifndef GETINPUTSYSTEM_H
#define GETINPUTSYSTEM_H

#include "ecs/core/EntityManager.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class GetInputSystem {
public:
  void update(EntityManager &em, const sf::Event &event);
};

#endif // GETINPUTSYSTEM_H
