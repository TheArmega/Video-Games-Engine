#include "imgui-SFML.h"
#include "imgui.h"

#include "circle.h"
#include "circleContainer.h"
#include "dataBase.h"

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

  // Open/Create db and create the table if not yet
  DataBase db("../circles.db");
  db.createTable();

  // Create example circles and add them to the db
  Circle circle1("circle1", true, 100.f, 10.f, 200.f, 300.f, 1.f, 1.f, 138, 206,
                 255);
  db.insertCircle(circle1);

  Circle circle2("circle2", true, 100.f, 10.f, 400.f, 600.f, 1.f, 1.f, 170, 51,
                 235);
  db.insertCircle(circle2);

  Circle circle3("circle3", true, 50.f, 10.f, 100.f, 700.f, 1.f, 1.f, 200, 100,
                 177);
  db.insertCircle(circle3);

  // Load data from db and insert it in circle container
  CircleContainer container("container");
  container.addCirclesFromVector(db.getAllCircles());

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
