
#include "app.h"
#include "circleContainer.h"
#include "dataBase.h"
#include "imgui.h"
#include "physicsEngine.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

bool uiBlockingActive = false;

CircleForm circleform;
CircleInformation circleInformation;

void App::run() {
  // Create the SFML window
  sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "VideoGameEngine");
  window.setFramerateLimit(FPS);

  // Initialize ImGui-SFML
  if (!ImGui::SFML::Init(window)) {
    std::cerr << "Failed to initialize ImGui-SFML\n";
    return;
  }

  // Open or create the database and create the table if it doesn't exist
  DataBase db("../circles.db");
  db.createTable();

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

    // Clear window
    window.clear();

    ImGui::SetNextWindowSize(ImVec2(300, 120), ImGuiCond_Always);
    ImGui::SetNextWindowPos({35, 35});
    ImGui::Begin("Circles Manager");
    if (ImGui::Button("Create Circle Form")) {
      circleform.renderCircleCreationWindow =
          !circleform.renderCircleCreationWindow;
    }
    if (ImGui::Button("Get circle information!")) {
      circleInformation.renderCircleInformationWindow =
          !circleInformation.renderCircleInformationWindow;
    }
    if (ImGui::Button("Save State")) {
      db.saveAllCircles(container);
    }
    if (ImGui::Button("Delete Circles")) {
      db.deleteAllCircles(container);
      container.setContainer(db.getAllCircles());
    }
    ImGui::End();

    if (circleform.renderCircleCreationWindow) {
      App::showCircleCreationWindow(window, engine, container);
    }

    if (circleInformation.renderCircleInformationWindow) {
      App::showCircleInformationWindow(window, engine, container);
    }

    // Update state of circles
    engine.updateCirclesState(container);

    // Draw all circles from the container
    std::string errMsg = container.circlesToShape(window);

    if (!errMsg.empty()) {
      ImGui::OpenPopup("ErrorPopup");
      std::string popupErrorMsg = errMsg;
      App::showImGuiPopupErrorWindow(popupErrorMsg);
    }

    uiBlockingActive =
        circleform.renderCircleCreationWindow || circleform.activePopup;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
        !uiBlockingActive) {
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
}

void App::showImGuiPopupErrorWindow(const std::string popupErrorMsg) {

  circleform.activePopup = true;

  ImGui::SetNextWindowSize(ImVec2(300, 90), ImGuiCond_Always);
  ImGui::SetNextWindowPos({570, 495});
  if (ImGui::BeginPopupModal("ErrorPopup", NULL,
                             ImGuiWindowFlags_AlwaysAutoResize |
                                 ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove)) {

    ImGui::TextWrapped("%s", popupErrorMsg.c_str());
    ImGui::Separator();

    if (ImGui::Button("Cerrar")) {
      ImGui::CloseCurrentPopup();
      circleform.activePopup = false;
    }

    ImGui::EndPopup();
  } else
    circleform.activePopup = false;
}

void App::showCircleCreationWindow(sf::RenderWindow &w, PhysicsEngine &engine,
                                   CircleContainer &container) {

  ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_Always);
  ImGui::SetNextWindowPos({1050, 35});
  ImGui::Begin("Circle Creation Form");
  ImGui::Separator();

  ImGui::Text("Name:");
  ImGui::SameLine();
  ImGui::InputText("##Circle Name", circleform.name,
                   IM_ARRAYSIZE(circleform.name));

  float maxRadiusX = std::min(circleform.x, WIDTH - circleform.x);
  float maxRadiusY = std::min(circleform.y, HEIGHT - circleform.y);
  circleform.maxRadius = std::min(maxRadiusX, maxRadiusY);

  ImGui::Text("Radius:");
  ImGui::SameLine();
  ImGui::SliderFloat("##Radius", &circleform.radius, 10.f,
                     circleform.maxRadius);

  float xMinValid = 0 + circleform.radius;
  float xMaxValid = WIDTH - circleform.radius;
  ImGui::Text("X Position:");
  ImGui::SameLine();
  ImGui::SliderFloat("##X Position", &circleform.x, xMinValid, xMaxValid);

  float yMinValid = 0 + circleform.radius;
  float yMaxValid = HEIGHT - circleform.radius;
  ImGui::Text("Y Position:");
  ImGui::SameLine();
  ImGui::SliderFloat("##Y Position", &circleform.y, yMinValid, yMaxValid);

  ImGui::Text("Color");
  ImGui::SameLine();
  ImGui::ColorEdit3("##Color", circleform.color);

  circleform.cPrev.setRadius(circleform.radius);
  circleform.cPrev.setPointCount(100);
  circleform.cPrev.setOrigin(
      {circleform.cPrev.getRadius(), circleform.cPrev.getRadius()});
  circleform.cPrev.setPosition({circleform.x, circleform.y});
  circleform.cPrev.setFillColor(sf::Color((int)(circleform.color[0] * 255),
                                          (int)(circleform.color[1] * 255),
                                          (int)(circleform.color[2] * 255)));
  w.draw(circleform.cPrev);

  if (ImGui::Button("Create cirlce")) {
    Circle c(static_cast<std::string>(circleform.name), true, circleform.radius,
             0.f, circleform.x, circleform.y, 0.f, 0.f,
             (int)(circleform.color[0] * 255), (int)(circleform.color[1] * 255),
             (int)(circleform.color[2] * 255));
    if (engine.circleInWindowArea(c)) {
      std::string errMsg = container.addCircle(c);
      if (!errMsg.empty()) {
        circleform.popupErrorMsg = errMsg;
        circleform.requestOpenErrorPopup = true;
      }
    } else {
      std::string errMsg = "Circle need to be inside the window!";
      circleform.popupErrorMsg = errMsg;
      circleform.requestOpenErrorPopup = true;
    }
  }

  if (ImGui::Button("Close")) {
    circleform.renderCircleCreationWindow =
        !circleform.renderCircleCreationWindow;
  }

  ImGui::End();

  if (circleform.requestOpenErrorPopup) {
    ImGui::OpenPopup("ErrorPopup");
    circleform.requestOpenErrorPopup = false;
  }

  showImGuiPopupErrorWindow(circleform.popupErrorMsg);
}

void App::showCircleInformationWindow(sf::RenderWindow &w,
                                      PhysicsEngine &engine,
                                      CircleContainer &container) {

  ImGui::SetNextWindowSize(ImVec2(200, 165), ImGuiCond_Always);
  ImGui::SetNextWindowPos({700, 35});
  ImGui::Begin("Circle Information");

  if (circleInformation.activeCircle != nullptr) {
    Circle &c = *circleInformation.activeCircle;

    ImGui::Text("Name: %s", c.getName().c_str());
    ImGui::Text("Radius %.2f", c.getRadius());
    ImGui::Text("X Position %.2f", c.getXPos());
    ImGui::Text("Y Position %.2f", c.getYPos());
    ImGui::Text("Velocity: (%.2f, %.2f)", c.getXVel(), c.getYVel());

    ImGui::Text("Color:");
    ImGui::SameLine();
    float color[3] = {(float)c.getRColor() / 255, (float)c.getGColor() / 255,
                      (float)c.getBColor() / 255};
    ImGui::ColorEdit3("##Color Information", color);
  }

  if (ImGui::Button("Close")) {
    circleInformation.renderCircleInformationWindow =
        !circleInformation.renderCircleInformationWindow;
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    sf::Vector2f mousePosition = engine.getMousePoint(w);

    for (auto &c : container.getContainer()) {
      if (engine.pointInCircleArea(c, mousePosition)) {
        circleInformation.activeCircle = &c;
      }
    }
  }

  ImGui::End();
}
