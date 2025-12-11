#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "core/Engine.h"
#include "core/Window.h"

Engine::Engine(std::string _name) : name(_name) {};

std::string Engine::getName() { return name; }

void Engine::run() {
  sf::Clock deltaClock;
  Window titleWindow("Title Window", 1440, 1080, 60);

  if (titleWindow.checkWindow()) {
    sf::RenderWindow &tw = titleWindow.getSfWindow();
    Vec2 windowCenter(titleWindow.getWidth() / 2, titleWindow.getHeight() / 2);

    while (tw.isOpen()) {

      while (const std::optional event =
                 titleWindow.getSfWindow().pollEvent()) {
        ImGui::SFML::ProcessEvent(titleWindow.getSfWindow(), *event);

        // Close window if requested
        if (event->is<sf::Event::Closed>())
          titleWindow.getSfWindow().close();
      }
      // Limpiar primero
      titleWindow.getSfWindow().clear(sf::Color(30, 30, 30));

      // Logic of window
      titleWindow.drawText("GAME", 120, sf::Color::White,
                           {windowCenter.x, windowCenter.y});

      // Update ImGui-SFML
      ImGui::SFML::Update(titleWindow.getSfWindow(), deltaClock.restart());

      ImGui::SFML::Render(titleWindow.getSfWindow());
      titleWindow.getSfWindow().display();
    }
    ImGui::SFML::Shutdown();
  }
}
