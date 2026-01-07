#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "core/Window.h"
#include "ecs/core/EntityManager.h"
#include "ecs/systems/GetInputSystem.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/PlayerControlSystem.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class GameScene : public Scene {
private:
  Window *window;
  MovementSystem movementSystem;
  GetInputSystem getInputSystem;
  PlayerControlSystem playerControlSystem;

public:
  explicit GameScene(Window *w, EntityManager *em);

  void init() override;
  void update(float dt) override;
  void render() override;
  void cleanUp() override;
  void handleEvent(const sf::Event &event) override;
};

#endif // GAMESCENE_H
