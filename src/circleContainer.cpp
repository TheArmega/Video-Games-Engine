/**
 * @file circleContainer.cpp
 * @brief CircleContainer class implementation
 * @ingroup CircleContainerModule
 *
 * Implements the CircleContainer constructor, setters, getters, and management
 * methods.
 */

#include "circleContainer.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <unordered_map>

// =======================
// Constructor
// =======================
CircleContainer::CircleContainer(
    std::string _name,
    std::unordered_map<std::string, sf::CircleShape> _container)
    : name(_name), container(_container) {}

// =======================
// Setters
// =======================
void CircleContainer::setName(std::string n) { name = n; }

// =======================
// Getters
// =======================
std::string CircleContainer::getName() const { return name; }

const std::unordered_map<std::string, sf::CircleShape> &
CircleContainer::getContainer() const {
  return container;
}

// =======================
// Methods
// =======================
void CircleContainer::addCircle(const Circle &c) {
  sf::CircleShape shape(c.getRadius());
  shape.setFillColor(sf::Color(c.getRColor(), c.getGColor(), c.getBColor()));
  shape.setOrigin({c.getRadius(), c.getRadius()});
  shape.setPosition({c.getXPos(), c.getYPos()});

  container[c.getName()] = shape;
}

void CircleContainer::addCirclesFromVector(const std::vector<Circle> v) {
  sf::CircleShape shape;
  for (const auto &c : v) {
    shape.setRadius(c.getRadius());
    shape.setFillColor(sf::Color(c.getRColor(), c.getGColor(), c.getBColor()));
    shape.setOrigin({c.getRadius(), c.getRadius()});
    shape.setPosition({c.getXPos(), c.getYPos()});

    container[c.getName()] = shape;
  }
}

void CircleContainer::delCircle(const std::string &circleName) {
  container.erase(circleName);
}

int CircleContainer::getSize() const {
  return static_cast<int>(container.size());
}
