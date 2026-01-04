#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "core/Window.h"
#include "ecs/core/EntityManager.h"
#include "scenes/Scene.h"
#include "ui/Button.h"
#include "ui/Title.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class TitleScene : public Scene {
private:
  Window *window;
  Title title;
  Button startButton;
  Button closeButton;
  sf::Clock deltaClock;

public:
  explicit TitleScene(Window *w, EntityManager *em);

  // Methods
  void init() override;
  void update(float dt) override;
  void render() override;
  void cleanUp() override;
  void handleEvent(const sf::Event &event) override;
};

#endif // TITLESCENE_H
