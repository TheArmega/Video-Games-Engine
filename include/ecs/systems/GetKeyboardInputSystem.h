#ifndef GETKEYBOARDINPUTSYSTEM_H
#define GETKEYBOARDINPUTSYSTEM_H

#include "ecs/core/EntityManager.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class GetKeyboardInputSystem {
public:
  void update(EntityManager &em, const sf::Event &event);
};

#endif // GETKEYBOARDINPUTSYSTEM_H
