#ifndef ENGINE_H
#define ENGINE_H

#include "core/Window.h"
#include "scenes/SceneManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Engine {

private:
  Window window;
  SceneManager sceneManager;

public:
  Engine();
  void run();
};

#endif // ENGINE_H
