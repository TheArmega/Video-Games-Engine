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
CircleContainer::CircleContainer(std::string _name,
                                 std::vector<Circle> _container)
    : name(_name), container(_container) {}

// =======================
// Setters
// =======================
void CircleContainer::setName(std::string n) { name = n; }
void CircleContainer::setContainer(std::vector<Circle> c) { container = c; }

// =======================
// Getters
// =======================
std::string CircleContainer::getName() const { return name; }
const std::vector<Circle> &CircleContainer::getContainer() const {
  return container;
}

// =======================
// Methods
// =======================
void CircleContainer::addCircle(const Circle &c) { container.push_back(c); }

void CircleContainer::delCircle(const std::string &circleName) {
  std::erase_if(container,
                [&](Circle &c) { return c.getName() == circleName; });
}

int CircleContainer::getSize() const { return container.size(); }

std::vector<sf::CircleShape> CircleContainer::circlesToShape() {
  sf::CircleShape shape;
  std::vector<sf::CircleShape> v;

  for (const auto &c : container) {
    shape.setRadius(c.getRadius());
    shape.setPointCount(100);
    shape.setFillColor(sf::Color(c.getRColor(), c.getGColor(), c.getBColor()));
    shape.setOrigin({c.getRadius(), c.getRadius()});
    shape.setPosition({c.getXPos(), c.getYPos()});

    v.push_back(shape);
  }

  return v;
}

void CircleContainer::updateCirclesState() {
  for (auto &c : container) {
    c.setXPos(c.getXPos() + c.getXVel());
    c.setYPos(c.getYPos() + c.getYVel());
  }
}
