#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scenes/Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class SceneManager {
private:
  std::unique_ptr<Scene> currentScene;

public:
  // Constructor
  SceneManager() = default;
  ~SceneManager();

  // Setters
  void setScene(std::unique_ptr<Scene> scene);

  void update(float deltaTime);
  void render(sf::RenderWindow &window);
};

#endif // SCENEMANAGER_H
