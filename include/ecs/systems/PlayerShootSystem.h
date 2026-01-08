#ifndef PLAYERSHOOTSYSTEM
#define PLAYERSHOOTSYSTEM

#include "ecs/core/EntityManager.h"
#include <SFML/Window/Window.hpp>
class PlayerShootSystem {

public:
  void update(EntityManager &em, sf::Window &w);
};

#endif // PLAYERSHOOTSYSTEM
