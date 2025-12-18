#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "core/Window.h"
#include "scenes/Scene.h"
#include "ui/Button.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class TitleScene : public Scene {
private:
  Window *window;
  Button startButton;
  Button closeButton;
  sf::Clock deltaClock;

public:
  explicit TitleScene(Window *w);

  void init() override;
  void update(float deltaTime) override;
  void render(sf::RenderWindow &w) override;
  void cleanUp() override;
  void handleEvent(const sf::Event &event) override;
};

#endif // TITLESCENE_H
