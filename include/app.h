/**
 * @file app.h
 * @author Jaime
 * @brief App class declaration
 * @version 0.1
 * @date 13/11/25
 *
 * @defgroup AppModule App Class
 * @brief Manages SFML ImGui windows and the main function of the program
 * @{
 */

#ifndef APP_H
#define APP_H

#include "circleContainer.h"
#include "physicsEngine.h"

#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/// @brief This variable tells if a UI is active and blocking the interaction
/// with the circles.
extern bool uiBlockingActive;

/// @brief This struct is used as a form to create and visualize at the same
/// time a circle.
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

/// @brief This struct is used to use the Circle Information Window.
struct CircleInformation {
  bool renderCircleInformationWindow = false;
  Circle *activeCircle = nullptr;
};

/**
 * @class App
 * @brief Handles the SFML and ImGui windows and has the main function of the
 * program.
 *
 * This class allows creating a Circle Information and a Circle Creation window,
 * also it contains all the buttons to interact with the program.
 */
class App {

private:
  /**
   * @brief Creates an ImGui window popup with an error.
   * @param String that indicates the error msg.
   */
  static void showImGuiPopupErrorWindow(const std::string popupErrorMsg);
  /**
   * @brief Creates the Circle Creation Window with ImGui.
   * @param The window itself, the motor engine and the container with all the
   * circles.
   */
  static void showCircleCreationWindow(sf::RenderWindow &w,
                                       PhysicsEngine &engine,
                                       CircleContainer &container);
  /**
   * @brief Creates the Circle Information Window with ImGui.
   * @param The window itself, the motor engine and the container with all the
   * circles.
   */
  static void showCircleInformationWindow(sf::RenderWindow &w,
                                          PhysicsEngine &engine,
                                          CircleContainer &container);

public:
  App();
  ~App();
  /**
   * @brief Run the main SFML window, load the data from the data base and
   * creates the ImGui window with the buttons to start interacting.
   */
  static void run();
};

#endif // APP_H
