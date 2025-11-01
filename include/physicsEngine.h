#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "circle.h"
#include "circleContainer.h"
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <iostream>

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
  std::string getame() const;
  Circle getActiveCircle() const;
  // }

  /// @name Methods
  /// @{
  /**
   * @brief Manage when a click in a circle is produced to push the circle
   * @param Window of SMFL, container with all the circles and bool checker
   */
  void drawLineWithMouse(sf::RenderWindow &w, CircleContainer &container,
                         bool &keepPushing);
  void pushCircleWhenRelease(sf::RenderWindow &w);
  // }
};

#endif // PHYSICSENGINE_H
