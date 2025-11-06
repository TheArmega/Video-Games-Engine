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

  static char name[64] = {0};
  static float radius = 10.f;
  static float x = 720;
  static float y = 540;
  static float color[3] = {(float)204 / 255, (float)77 / 255, (float)5 / 255};

  bool creationCircleWindow = false;

  sf::CircleShape cPrev;
  float maxRadius;
  float xMinValid, xMaxValid, yMinValid, yMaxValid;

  // Error msg for popups
  static std::string popupErrorMsg = "";
  static bool requestOpenErrorPopup = false;
  static bool activePopup = false;

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
    ImGui::Begin("Circles Manager");
    if (ImGui::Button("Create Circle")) {
      creationCircleWindow = true;
    }
    ImGui::Button("Get circle information!");
    ImGui::End();

    // Clear window
    window.clear();

    if (creationCircleWindow) {

      ImGui::Begin("Circle Creation Form");
      ImGui::Separator();

      ImGui::Text("Name:");
      ImGui::SameLine();
      ImGui::InputText("##Circle Name", name, IM_ARRAYSIZE(name));

      if (0 <= x - 300.f && WIDTH >= x + 300.f && 0 <= y - 300.f &&
          HEIGHT >= y + 300.f) {
        maxRadius = 300.f;
      } else {
        maxRadius = std::min({x, WIDTH - x, y, HEIGHT - y});
      }
      ImGui::Text("Radius:");
      ImGui::SameLine();
      ImGui::SliderFloat("##Radius", &radius, 10.f, maxRadius);

      xMinValid = 0 + radius;
      xMaxValid = WIDTH - radius;
      ImGui::Text("X Position:");
      ImGui::SameLine();
      ImGui::SliderFloat("##X Position", &x, xMinValid, xMaxValid);

      yMinValid = 0 + radius;
      yMaxValid = HEIGHT - radius;
      ImGui::Text("Y Position:");
      ImGui::SameLine();
      ImGui::SliderFloat("##Y Position", &y, yMinValid, yMaxValid);

      ImGui::Text("Color");
      ImGui::SameLine();
      ImGui::ColorEdit3("##Color", color);

      cPrev.setRadius(radius);
      cPrev.setPointCount(100);
      cPrev.setOrigin({cPrev.getRadius(), cPrev.getRadius()});
      cPrev.setPosition({x, y});
      cPrev.setFillColor(sf::Color((int)(color[0] * 255), (int)(color[1] * 255),
                                   (int)(color[2] * 255)));
      window.draw(cPrev);

      if (ImGui::Button("Create cirlce")) {
        Circle c(static_cast<std::string>(name), true, radius, 0.f, x, y, 0.f,
                 0.f, (int)(color[0] * 255), (int)(color[1] * 255),
                 (int)(color[2] * 255));
        if (engine.circleInWindowArea(c)) {
          std::string errMsg = container.addCircle(c);
          if (!errMsg.empty()) {
            popupErrorMsg = errMsg;
            requestOpenErrorPopup = true;
          }
        } else {
          popupErrorMsg = "Circle need to be inside the window!";
          requestOpenErrorPopup = true;
        }

        creationCircleWindow = false;
      }

      ImGui::End();
    }

    // Update state of circles
    engine.updateCirclesState(container);

    // Draw all circles from the container
    std::string errMsg = container.circlesToShape(window);

    if (!errMsg.empty()) {
      popupErrorMsg = errMsg;
      requestOpenErrorPopup = true;
    }

    if (requestOpenErrorPopup) {
      ImGui::OpenPopup("ErrorPopup");
      requestOpenErrorPopup = false;
      activePopup = true;
    }
    ImGui::SetNextWindowSize(ImVec2(300, 90), ImGuiCond_Always);
    ImGui::SetNextWindowPos({570, 495});
    if (ImGui::BeginPopupModal("ErrorPopup", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize |
                                   ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove)) {
      ImGui::TextWrapped("%s", popupErrorMsg.c_str());
      ImGui::Separator();

      if (ImGui::Button("Cerrar")) {
        activePopup = false;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !activePopup) {
      engine.drawLineWithMouse(window, container);
    } else {
      if (keepPushingMouseButton) {
        engine.pushCircleWhenRelease(window);
      }
      keepPushingMouseButton = false;
      engine.setActiveCircle(nullptr);
    }

    // Render ImGui and display
    ImGui::SFML::Render(window);
    window.display();
  }

  // Shutdown ImGui-SFML
  ImGui::SFML::Shutdown();
}
