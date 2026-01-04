#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "SceneCommand.h"
#include "ecs/core/EntityManager.h"

class Scene {
protected:
  std::string name;
  SceneCommand command = SceneCommand::None;
  EntityManager *entityManager;

public:
  // Constructor
  explicit Scene(const std::string _name, EntityManager *_entityManager);
  virtual ~Scene() = default;

  // Getters
  std::string getName();

  // Virtual Methods
  // Init scene
  virtual void init();

  // Update scene, logic in it
  virtual void update();

  // Render scene
  virtual void render(sf::RenderWindow &w);

  // Clean resources in scene
  virtual void cleanUp();

  // Handle events depending of the elements of the scene
  virtual void handleEvent(const sf::Event &event);

  // Comands
  SceneCommand getCommand() const;
  void clearCommand();
};

#endif // SCENE_H
