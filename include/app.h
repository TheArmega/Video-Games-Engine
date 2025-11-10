#ifndef APP_H
#define APP_H

#include "circleContainer.h"
#include "physicsEngine.h"

#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

extern bool uiBlockingActive;

struct CircleForm {
  bool renderCircleCreationWindow = false;
  sf::CircleShape cPrev;
  char name[64] = {0};
  float radius = 10.f;
  float maxRadius = 300.f;
  float x = 720.f;
  float y = 540.f;
  float color[3] = {204.f / 255.f, 77.f / 255.f, 5.f / 255.f};
  bool requestOpenErrorPopup = false;
  bool activePopup = false;
  std::string popupErrorMsg;
};

struct CircleInformation {
  bool renderCircleInformationWindow = false;
  Circle *activeCircle = nullptr;
};

class App {

private:
  static void showImGuiPopupErrorWindow(const std::string popupErrorMsg);
  static void showCircleCreationWindow(sf::RenderWindow &w,
                                       PhysicsEngine &engine,
                                       CircleContainer &container);
  static void showCircleInformationWindow(sf::RenderWindow &w,
                                          PhysicsEngine &engine,
                                          CircleContainer &container);

public:
  App();
  ~App();
  static void run();
};

#endif // APP_H
