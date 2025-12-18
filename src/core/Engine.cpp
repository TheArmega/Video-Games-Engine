#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <any>
#include <iostream>
#include <memory>

#include "core/Engine.h"
#include "core/ImGuiLayer.h"
#include "core/Window.h"

#include "scenes/SceneManager.h"
#include "scenes/TitleScene.h"
#include "ui/Button.h"

Engine::Engine() : window("Main Window", 1440, 1080, 60), sceneManager() {}

void Engine::run() {

  sf::RenderWindow &w = window.getSfWindow();

  SceneManager sceneManager;

  sceneManager.setScene(std::make_unique<TitleScene>(&window));

  sf::Clock clock;

  while (w.isOpen()) {

    while (const std::optional event = w.pollEvent()) {
      ImGui::SFML::ProcessEvent(w, *event);

      // Close window if requested
      if (event->is<sf::Event::Closed>())
        w.close();

      sceneManager.eventHandler(*event);
    }

    float dt = clock.restart().asSeconds();

    sceneManager.update(dt);
    w.clear();
    sceneManager.render(w);
    w.display();
  }
}
