#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "core/Window.h"
#include "ecs/core/EntityManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class GameScene : public Scene {
private:
  Window *window;

public:
  explicit GameScene(Window *w, EntityManager *em);

  void init() override;
  void update() override;
  void render(sf::RenderWindow &w) override;
  void cleanUp() override;
  void handleEvent(const sf::Event &event) override;
};

#endif // GAMESCENE_H
