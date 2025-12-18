#include "scenes/Scene.h"
#include "scenes/SceneCommand.h"
#include "scenes/SceneManager.h"
#include "scenes/TitleScene.h"
#include "ui/Button.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

TitleScene::TitleScene(Window *w)
    : Scene("Title Scene"), window(w),
      startButton("Start Button", "../assets/sprites/buttons/start-button.png",
                  "../assets/sprites/buttons/start-button-pressed.png",
                  {500, 400}),
      closeButton("Close Button", "../assets/sprites/buttons/close-button.png",
                  "../assets/sprites/buttons/close-button-pressed.png",
                  {800, 400}) {
  startButton.setOnClick([this]() { command = SceneCommand::GoToGame; });
  closeButton.setOnClick([this]() { command = SceneCommand::Exit; });
}

void TitleScene::init() {
  if (!ImGui::SFML::Init(window->getSfWindow())) {
    std::cerr << "Failed to initialize ImGui-SFML" << std::endl;
  }
}

void TitleScene::update(float deltaTime) {
  // Update ImGui-SFML
  ImGui::SFML::Update(window->getSfWindow(), deltaClock.restart());
  startButton.update(*window);
  closeButton.update(*window);
}

void TitleScene::render(sf::RenderWindow &w) {
  w.clear(sf::Color(30, 30, 30));
  // window->drawText("GAME", 120, sf::Color::White, {550, 200});
  startButton.draw(*window);
  closeButton.draw(*window);
  ImGui::SFML::Render(w);
  w.display();
}

void TitleScene::cleanUp() { ImGui::SFML::Shutdown(); }

void TitleScene::handleEvent(const sf::Event &event) {
  startButton.handleEvent(event, *window);
  closeButton.handleEvent(event, *window);
}
