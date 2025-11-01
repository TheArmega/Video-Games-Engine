/**
 * @file main.cpp
 * @brief Entry point for the VideoGameEngine using SFML and ImGui-SFML
 * @author Jaime
 * @version 0.1
 * @date 23/10/25
 *
 * @details
 * This file initializes the SFML window and ImGui-SFML integration,
 * manages the Circle database, populates a CircleContainer, and runs
 * the main render loop displaying circles and ImGui widgets.
 */

#include "imgui-SFML.h"
#include "imgui.h"

#include "circle.h"
#include "circleContainer.h"
#include "dataBase.h"
#include "physicsEngine.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include <SFML/Window/Mouse.hpp>
#include <iostream>

/**
 * @brief Main function of the VideoGameEngine
 *
 * Initializes the window and ImGui-SFML, creates example Circle objects,
 * stores them in the database, populates the CircleContainer, and runs
 * the main render loop with ImGui GUI elements.
 *
 * @return int Returns 0 on success, -1 on failure (ImGui initialization
 * failure)
 */
int main() {
  // Window dimensions

  // Create the SFML window
  sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "VideoGameEngine");
  window.setFramerateLimit(FPS);

  // Initialize ImGui-SFML
  if (!ImGui::SFML::Init(window)) {
    std::cerr << "Failed to initialize ImGui-SFML\n";
    return -1;
  }

  // Open or create the database and create the table if it doesn't exist
  DataBase db("../circles.db");
  db.createTable();

  // Create example Circle objects
  Circle circle1("circle1", true, 100.f, 10.f, 200.f, 300.f, 0.f, 0.f, 138, 206,
                 255);
  db.insertCircle(circle1);

  Circle circle2("circle2", true, 100.f, 10.f, 400.f, 600.f, 0.f, 0.f, 170, 51,
                 235);
  db.insertCircle(circle2);

  Circle circle3("circle3", true, 50.f, 10.f, 100.f, 700.f, 0.f, 0.f, 200, 100,
                 177);
  db.insertCircle(circle3);

  // Load data from database and insert it into a CircleContainer
  CircleContainer container("container", db.getAllCircles());

  // Create PhysicsEngine
  PhysicsEngine engine("Engine");

  sf::Clock deltaClock;

  bool keepPushingMouse = false;

  // Main render loop
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      // Close window if requested
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // Update ImGui-SFML
    ImGui::SFML::Update(window, deltaClock.restart());

    // Example custom ImGui window
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    // Clear window
    window.clear();

    // Update state of circles
    engine.updateCirclesState(container);

    // Draw all circles from the container
    container.circlesToShape(window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      engine.drawLineWithMouse(window, container, keepPushingMouse);
    } else {
      if (keepPushingMouse) {
        engine.pushCircleWhenRelease(window);
      }
      keepPushingMouse = false;
      engine.setActiveCircle(nullptr);
    }

    // Render ImGui and display
    ImGui::SFML::Render(window);
    window.display();
  }

  // Shutdown ImGui-SFML
  ImGui::SFML::Shutdown();
}
