#include "scenes/Scene.h"
#include "scenes/SceneCommand.h"
#include "scenes/SceneManager.h"
#include "scenes/TitleScene.h"
#include "ui/Button.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include "ui/Title.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

TitleScene::TitleScene(Window *w)
    : Scene("Title Scene"), window(w),
      title("Game Title", "../assets/sprites/titles/title.png", {450, 200},
            {14, 14}),
      startButton("Start Button", "../assets/sprites/buttons/start-button.png",
                  "../assets/sprites/buttons/start-button-pressed.png",
                  {150, 700}, {8, 8}),
      closeButton("Close Button", "../assets/sprites/buttons/close-button.png",
                  "../assets/sprites/buttons/close-button-pressed.png",
                  {750, 700}, {8, 8}) {
  startButton.setOnClick([this]() { command = SceneCommand::GoToGame; });
  closeButton.setOnClick([this]() { command = SceneCommand::Exit; });
}

void TitleScene::init() { return; }

void TitleScene::update() {
  // Update Scene
  startButton.update(*window);
  closeButton.update(*window);
}

void TitleScene::render(sf::RenderWindow &w) {
  //  Draw Title Sprite
  w.draw(title.getSprite());

  // Draw Buttons Sprite
  w.draw(startButton.getSprite());
  w.draw(closeButton.getSprite());

  // Draw Bounding Box to debug
  // startButton.drawBoundingBox(*window);
  // closeButton.drawBoundingBox(*window);
}

void TitleScene::cleanUp() { return; }

void TitleScene::handleEvent(const sf::Event &event) {
  startButton.handleEvent(event, *window);
  closeButton.handleEvent(event, *window);
}
