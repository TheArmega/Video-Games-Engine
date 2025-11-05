/**
 * @file circleContainer.cpp
 * @brief CircleContainer class implementation
 * @ingroup CircleContainerModule
 *
 * Implements the CircleContainer constructor, setters, getters, and management
 * methods.
 */

#include "circleContainer.h"
#include "imgui.h"
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
void CircleContainer::addCircle(const Circle &c) {
  std::string name = c.getName();

  for (auto &_c : container) {
    if (_c.getName() == name) {
      ImGui::Begin(
          "Can't add circle with the same name as other in the program!");
      ImGui::End();

      return;
    }
  }
  container.push_back(c);
}

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
