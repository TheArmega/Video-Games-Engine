#include "imgui-SFML.h"
#include "imgui.h"

<<<<<<< Updated upstream
=======
#include "circle.h"
#include "circleContainer.h"

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color(138, 206, 0));
  shape.setOrigin({shape.getRadius(), shape.getRadius()});
  shape.setPosition({float(width) / 2, float(height) / 2});
=======
  CircleContainer container("container");
  Circle circle1("circle1", true, 100.f, 10.f, 200.f, 300.f, 1.f, 1.f, 138, 206,
                 255);
  container.addCircle(circle1);
  Circle circle2("circle2", true, 100.f, 10.f, 400.f, 600.f, 1.f, 1.f, 170, 51,
                 235);
  container.addCircle(circle2);

  // container.delCircle(circle2.getName());
>>>>>>> Stashed changes

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

    for (const auto &pair : container.getContainer()) {
      window.draw(pair.second);
    }

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
