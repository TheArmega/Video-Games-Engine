#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class Scene {
protected:
  std::string name;

public:
  // Constructor
  explicit Scene(std::string _name);
  virtual ~Scene() = default;

  // Getters
  std::string getName();

  // Virtual Methods
  // Init scene
  virtual void init();

  // Update scene, logic in it
  virtual void update(float deltaTime);

  // Render scene
  virtual void render(sf::RenderWindow &w);

  // Clean resources in scene
  virtual void cleanUp();
};

#endif // SCENE_H
