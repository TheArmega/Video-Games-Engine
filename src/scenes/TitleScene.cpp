#include "scenes/Scene.h"
#include "scenes/TitleScene.h"
#include "ui/Button.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

TitleScene::TitleScene(Window *w)
    : Scene("Title Scene"), window(w),
      startButton("Start Button", "../assets/sprites/buttons/start-button.png",
                  "../assets/sprites/buttons/start-button-pressed.png", 500,
                  500) {}

void TitleScene::init() {
  if (!ImGui::SFML::Init(window->getSfWindow())) {
    std::cerr << "Failed to initialize ImGui-SFML" << std::endl;
  }
}

void TitleScene::update(float deltaTime) {
  // Update ImGui-SFML
  ImGui::SFML::Update(window->getSfWindow(), deltaClock.restart());
}

void TitleScene::render(sf::RenderWindow &w) {
  w.clear(sf::Color(30, 30, 30));
  window->drawText("GAME", 120, sf::Color::White, {100, 100});
  ImGui::SFML::Render(w);
}

void TitleScene::cleanUp() {
  ImGui::SFML::Shutdown();
}

;
