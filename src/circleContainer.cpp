/**
 * @file circleContainer.cpp
 * @brief CircleContainer class implementation
 * @ingroup CircleContainerModule
 *
 * Implements the CircleContainer constructor, setters, getters, and management
 * methods.
 */

#include "circleContainer.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <array>
#include <cmath>

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
std::vector<Circle> &CircleContainer::getContainer() { return container; }

// =======================
// Methods
// =======================
void CircleContainer::addCircle(const Circle &c) { container.push_back(c); }

void CircleContainer::delCircle(const std::string &circleName) {
  std::erase_if(container,
                [&](Circle &c) { return c.getName() == circleName; });
}

int CircleContainer::getSize() const { return container.size(); }

void CircleContainer::circlesToShape(sf::RenderWindow &w) {
  sf::CircleShape shape;

  for (const auto &c : container) {
    shape.setRadius(c.getRadius());
    shape.setPointCount(100);
    shape.setFillColor(sf::Color(c.getRColor(), c.getGColor(), c.getBColor()));
    shape.setOrigin({c.getRadius(), c.getRadius()});
    shape.setPosition({c.getXPos(), c.getYPos()});

    w.draw(shape);
  }
}

void CircleContainer::updateCirclesState(int width, int height) {

  float x, y, vx, vy, r;

  for (auto &c : container) {

    float x = c.getXPos();
    float y = c.getYPos();
    float vx = c.getXVel();
    float vy = c.getYVel();
    float r = c.getRadius();

    x += vx;
    y += vy;

    if (x + r >= width || x - r <= 0) {
      vx = -vx;
      x = std::clamp(x, r, static_cast<float>(width) - r);
    }

    if (y + r >= height || y - r <= 0) {
      vy = -vy;
      y = std::clamp(y, r, static_cast<float>(height) - r);
    }

    c.setXPos(x);
    c.setYPos(y);
    c.setXVel(vx);
    c.setYVel(vy);
  }
}
