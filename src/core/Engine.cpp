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

void Engine::run() {

  sf::RenderWindow &w = window.getSfWindow();

  sceneManager.setScene(std::make_unique<TitleScene>(&window));

  sf::Clock clock;

  if (!ImGui::SFML::Init(w)) {
    std::cerr << "Can't create ImGui-SFML instance.";
    return;
  }

  while (w.isOpen()) {

    while (const std::optional event = w.pollEvent()) {
      ImGui::SFML::ProcessEvent(w, *event);

      // Close window if requested
      if (event->is<sf::Event::Closed>())
        w.close();

      sceneManager.eventHandler(*event);
    }

    sf::Time dt = clock.restart();

    SceneCommand cmd = sceneManager.getActiveCommand();

    switch (cmd) {
    case SceneCommand::Exit:
      w.close();
      break;

    case SceneCommand::GoToGame:
      sceneManager.setScene(std::make_unique<GameScene>(&window));
      break;

    default:
      break;
    }
    sceneManager.clearActiveCommand();

    ImGui::SFML::Update(w, dt);
    sceneManager.update();

    w.clear(sf::Color(43, 48, 58));

    ImGui::SFML::Render(w);
    sceneManager.render(w);
    w.display();
  }
}
