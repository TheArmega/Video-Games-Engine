/**
 * @file phisicsEngine.h
 * @author Jaime
 * @brief PhysicsEngine class declaration
 * @version 0.1
 * @date 23/10/25
 *
 * @defgroup PhysicsEngineModule PhysicsEngine Class
 * @brief A group of methods to simulate physics between circles.
 * @{
 */

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "circle.h"
#include "circleContainer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <iostream>
#include <optional>
#include <vector>

extern const unsigned int WIDTH;
extern const unsigned int HEIGHT;
extern const int FPS;
extern bool keepPushingMouseButton;
extern const float FORCE_SCALE;
extern const float DAMPING_COEFFICIENT;
extern const float e;

/**
 * @class PhysicsEngine
 * @brief Handles the interaction between circles.
 */
class PhysicsEngine {

private:
  std::string name = "Engine";
  Circle *activeCircle = nullptr;

public:
  PhysicsEngine(std::string _name = "Engine", Circle *_activeCircle = nullptr);

  /// @name Setters
  /// @ {
  void setName(std::string n);
  void setActiveCircle(Circle *c);
  // }

  /// @name Getters
  /// @ {
  std::string getName() const;
  Circle getActiveCircle() const;
  // }

  /// @name Methods
  /// @{

  /**
   * @brief Apply friction to a circle speed.
   * @param Circle object.
   */
  void applyFrictionForce(Circle &c);

  /**
   * @brief Updates state of all circles, position, speed and check collisions
   * @param Container with all circles.
   */
  void updateCirclesState(CircleContainer &container);

  /**
   * @brief Get the mouse pointer position.
   * @param SFML window.
   * @return Vector with coordinates of mouse pointer.
   */
  sf::Vector2f getMousePoint(sf::RenderWindow &w);

  /**
   * @brief Check if a point is inside a circle area.
   * @param Circle object and point.
   * @return True if point in circle.
   */
  static bool pointInCircleArea(const Circle &c, const sf::Vector2f &p);

  /**
   * @brief Check if a circle is inside the window.
   * @param Circle object.
   * @return True if circle in window.
   */
  bool circleInWindowArea(const Circle &c);

  /**
   * @brief Calculate the intersection point between a point outside the area of
   * the circle and the center of the circle.
   * @param Circle object and point.
   * @return Intersection point.
   */
  std::optional<sf::Vector2f> getIntersectionPoint(const Circle c,
                                                   const sf::Vector2f p);

  /**
   * @brief Draw a line from the border of the circle to the mouse pointer when
   * keep pressed mouse left button.
   * @param Window of SMFL, container with all the circles and bool checker.
   */
  void drawLineWithMouse(sf::RenderWindow &w, CircleContainer &container);

  /**
   * @brief Push a circle in a direction when release click button.
   * @param Window of SMFL.
   */
  void pushCircleWhenRelease(sf::RenderWindow &w);

  /**
   * @brief Returns the dot product of two vectors.
   * @param Two vector.
   * @return The dot product of the vectors.
   */
  float dotProduct(const sf::Vector2f &v, const sf::Vector2f &_v);

  /**
   * @brief Returns the distance between two circles.
   * @param Two circles between which you want to calculate the distance.
   * @return The distance between the circles.
   */
  static float distanceBetweenCircles(const Circle &c, const Circle &_c);

  /**
   * @brief Check if two circles collide.
   * @param Two circles between which you want to check if collide.
   * @return A bool that represents if two circles collide.
   */
  static bool circlesCollide(const Circle &c, const Circle &_c);

  /**
   * @brief Compute the direction of the collision vector between two circles.
   * @param Two circles between which you want claculate the direction vector.
   * @return A Vector2f with the direction.
   */
  sf::Vector2f computeDirectionCollisionVector(const Circle &c,
                                               const Circle &_c);

  /**
   * @brief Compute the relative velocity of two circles.
   * @param Two circles between which you want claculate the relative velocity.
   * @return A Vector2f with the relative velocity.
   */
  sf::Vector2f computeRelativeVelocity(const Circle &c, const Circle &_c);

  /**
   * @brief Detects and process collisions between two circles.
   * @param Container with all the circles.
   */
  void computeCollisionsBetweenCircles(CircleContainer &container);

  // }
};

#endif // PHYSICSENGINE_H
