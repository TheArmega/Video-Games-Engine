#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include <iostream>

int main() {

  int const width = 1440;
  int const height = 1080;

  sf::RenderWindow window(sf::VideoMode({width, height}), "VideoGameEngine");
  window.setFramerateLimit(60);

  if (!ImGui::SFML::Init(window)) {
    std::cerr << "Failed to initialize ImGui-SFML\n";
    return -1;
  }

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color(138, 206, 0));
  shape.setOrigin({shape.getRadius(), shape.getRadius()});
  shape.setPosition({float(width) / 2, float(height) / 2});

  sf::Clock deltaClock;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>())
        window.close();
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::ShowDemoWindow();

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
