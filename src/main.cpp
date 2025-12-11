#include "core/Engine.h"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "ImGui + SFML Test");

  if (!ImGui::SFML::Init(window)) {
    std::cerr << "Failed to initialize ImGui-SFML" << std::endl;
    return -1;
  }

  sf::Clock deltaClock;
  Engine engine; // Instancia única, no la recrees cada frame

  while (window.isOpen()) {

    // Nuevo sistema de eventos SFML3 (std::optional)
    while (auto eventOpt = window.pollEvent()) {
      const sf::Event &event = *eventOpt;

      ImGui::SFML::ProcessEvent(window, event);

      if (event.is<sf::Event::Closed>()) {
        window.close();
      }
    }

    // 1. Actualizar ImGui ANTES del Begin()
    ImGui::SFML::Update(window, deltaClock.restart());

    // 2. Comenzar ImGui frame
    ImGui::Begin("Hello, ImGui!");
    ImGui::Text("Engine name: %s", engine.getName().c_str());
    ImGui::End();

    // Ventana demo opcional
    ImGui::ShowDemoWindow();

    // 3. Render normal
    window.clear(sf::Color(30, 30, 30));

    // 4. Render ImGui
    ImGui::SFML::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}
