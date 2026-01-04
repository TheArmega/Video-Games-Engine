#include "ecs/core/EntityManager.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <any>
#include <iostream>
#include <memory>

#include "core/Engine.h"
#include "core/ImGuiLayer.h"
#include "core/Window.h"

#include "scenes/GameScene.h"
#include "scenes/SceneCommand.h"
#include "scenes/SceneManager.h"
#include "scenes/TitleScene.h"
#include "ui/Button.h"

Engine::Engine() : window("Main Window", 1440, 1080, 60), sceneManager() {}

void Engine::init() {

  sf::RenderWindow &w = window.getSfWindow();

  sceneManager.setScene(
      std::make_unique<TitleScene>(&window, &m_entityManager));

  if (!ImGui::SFML::Init(w)) {
    std::cerr << "Can't create ImGui-SFML instance.";
    return;
  }
}

void Engine::eventHandler() {
  sf::RenderWindow &w = window.getSfWindow();

  while (const std::optional event = w.pollEvent()) {
    ImGui::SFML::ProcessEvent(w, *event);

    // Close window if requested
    if (event->is<sf::Event::Closed>())
      w.close();

    sceneManager.eventHandler(*event);
  }
}

void Engine::activeCommand() {
  sf::RenderWindow &w = window.getSfWindow();

  SceneCommand cmd = sceneManager.getActiveCommand();

  switch (cmd) {
  case SceneCommand::Exit:
    w.close();
    break;

  case SceneCommand::GoToGame:
    sceneManager.setScene(
        std::make_unique<GameScene>(&window, &m_entityManager));
    break;

  default:
    break;
  }
  sceneManager.clearActiveCommand();
}

void Engine::updateUI(sf::Time dt) {
  sf::RenderWindow &w = window.getSfWindow();
  ImGui::SFML::Update(w, dt);
}

void Engine::render() {
  sf::RenderWindow &w = window.getSfWindow();

  ImGui::SFML::Render(w);
  sceneManager.render();
}

void Engine::mainLoop() {

  init();
  sf::RenderWindow &w = window.getSfWindow();

  sf::Clock clock;

  while (w.isOpen()) {

    eventHandler();
    activeCommand();
    sf::Time dtTime = clock.restart();
    float dt = dtTime.asSeconds();

    sceneManager.update(dt);
    m_entityManager.update();
    updateUI(dtTime);
    w.clear(sf::Color(43, 48, 58));
    render();
    w.display();

    m_currentFrame++;
  }
}
