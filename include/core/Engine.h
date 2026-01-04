#ifndef ENGINE_H
#define ENGINE_H

#include "core/Window.h"
#include "ecs/core/EntityManager.h"
#include "scenes/SceneManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Engine {

private:
  int m_currentFrame = 0;
  EntityManager m_entityManager;
  Window window;
  SceneManager sceneManager;

public:
  Engine();

  // Main Loop
  void mainLoop();

  // Main methods
  void init();
  void eventHandler();
  void updateUI(sf::Time dt);
  void render();
  void activeCommand();
};

#endif // ENGINE_H
