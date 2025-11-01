/**
 * @file physicsEngine.cpp
 * @brief PhysicsEngine class implementation
 * @ingroup CircleModule
 *
 * Implements the PhysicsEngine class constructor, with several methods
 */

#include "circleContainer.h"
#include "physicsEngine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <vector>

// ======================
// Constructor
// ======================
PhysicsEngine::PhysicsEngine(std::string _name, Circle *_activeCircle)
    : name(_name), activeCircle(_activeCircle) {}

// ======================
// Setters
// ======================
void PhysicsEngine::setName(std::string n) { name = n; }
void PhysicsEngine::setActiveCircle(Circle *c) { activeCircle = c; }

// ======================
// Getters
// ======================
std::string PhysicsEngine::getame() const { return name; }
Circle PhysicsEngine::getActiveCircle() const { return *activeCircle; }

// ======================
// Methods
// ======================
void PhysicsEngine::drawLineWithMouse(sf::RenderWindow &w,
                                      CircleContainer &container,
                                      bool &keepPushing) {
  sf::Vector2i mousePosition = sf::Mouse::getPosition(w);
  float x = mousePosition.x;
  float y = mousePosition.y;

  for (auto &c : container.getContainer()) {

    float dx = x - c.getXPos();
    float dy = y - c.getYPos();
    float r = c.getRadius();

    if ((dx * dx + dy * dy < r * r)) {
      keepPushing = true;
      if (activeCircle == nullptr)
        activeCircle = &c;
      break;
    }
  }

  if (keepPushing || activeCircle != nullptr) {

    float x_c = activeCircle->getXPos();
    float y_c = activeCircle->getYPos();
    std::array line = {sf::Vertex{sf::Vector2f(x_c, y_c)},
                       sf::Vertex{sf::Vector2f(x, y)}};

    float lineDistance = std::sqrt(std::pow(x - x_c, 2) + std::pow(y - y_c, 2));

    w.draw(line.data(), 2, sf::PrimitiveType::Lines);
  }
}

void PhysicsEngine::pushCircleWhenRelease(sf::RenderWindow &w) {
  float Cx = activeCircle->getXPos();
  float Cy = activeCircle->getYPos();
  float Cr = activeCircle->getRadius();

  sf::Vector2i mousePosition = sf::Mouse::getPosition(w);
  float Px = mousePosition.x;
  float Py = mousePosition.y;

  // Vector from C to P
  std::vector<float> v = {Px - Cx, Py - Cy};

  // Distance between C and P
  float distance = std::sqrt(v[0] * v[0] + v[1] * v[1]);

  // Point of intersection between C and Vector
  float Ix = Cx + (Cr / distance) * v[0];
  float Iy = Cy + (Cr / distance) * v[1];

  // Direction of F Vector
  std::vector<float> direction = {Ix - Px, Iy - Py};
  // Module of vector
  float module =
      std::sqrt(direction[0] * direction[0] + direction[1] * direction[1]);
  // Unit Vector
  std::vector<float> unitVector = {direction[0] / module,
                                   direction[1] / module};

  // Vector of force
  float f = 0.5 * distance;
  std::vector<float> forceVector = {unitVector[0] * f, unitVector[1] * f};

  // Vector of acceleration
  std::vector<float> acceVector = {forceVector[0] / activeCircle->getMass(),
                                   forceVector[1] / activeCircle->getMass()};

  activeCircle->setXVel(activeCircle->getXVel() + acceVector[0]);
  activeCircle->setYVel(activeCircle->getYVel() + acceVector[1]);
}
