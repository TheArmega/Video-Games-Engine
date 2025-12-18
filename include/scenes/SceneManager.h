#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scenes/Scene.h"
#include "scenes/SceneCommand.h"
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

  // Update state of the current scene
  void update(float deltaTime);

  // Render current window
  void render(sf::RenderWindow &window);

  // Handle events to current scene
  void eventHandler(const sf::Event &event);

  SceneCommand getActiveCommand() const;
  void clearActiveCommand();
};

#endif // SCENEMANAGER_H
