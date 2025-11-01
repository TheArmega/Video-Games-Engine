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
  bool pointInCircleArea(const Circle &c, const sf::Vector2f &p);
  /**
   * @brief Calculate the intersection point between a point outside the area of
   * the circle and the center of the circle.
   * @param Circle object and point.
   * @return Intersection point.
   */
  std::optional<sf::Vector2f> getIntersectionPoint(Circle c, sf::Vector2f p);
  /**
   * @brief Draw a line from the border of the circle to the mouse pointer.
   * @param Window of SMFL, container with all the circles and bool checker.
   */
  void drawLineWithMouse(sf::RenderWindow &w, CircleContainer &container,
                         bool &keepPushing);

  /**
   * @brief Push a circle in a direction when release click butom.
   * @param Window of SMFL.
   */
  void pushCircleWhenRelease(sf::RenderWindow &w);
  // }
};

#endif // PHYSICSENGINE_H
