/**
 * @file circleContainer.cpp
 * @brief CircleContainer class implementation
 * @ingroup CircleContainerModule
 *
 * Implements the CircleContainer constructor, setters, getters, and management
 * methods.
 */

#include "circle.h"
#include "circleContainer.h"
#include "imgui.h"
#include "physicsEngine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <array>
#include <cmath>
#include <iostream>

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
std::string CircleContainer::addCircle(Circle &c) {
  std::string name = c.getName();

  for (auto &_c : container) {
    if (_c.getName() == name)
      return "Can't add circle with the same name as other in the program!";

    if (PhysicsEngine::circlesCollide(c, _c))
      return "Can't draw circle in the same space as another circle!";

    static sf::Font font;
    static bool loaded = font.openFromFile("../resources/OpenSans.ttf");
    if (!loaded) {
      return "Can't open font file!";
    }
    sf::Text text(font);

    text.setString(c.getName());
    text.setCharacterSize((int)(0.5 * c.getRadius()));

    // Get position for first and last character
    std::size_t count = c.getName().size();
    float textWidth = 0.f;
    if (count > 0) {
      sf::Vector2f start = text.findCharacterPos(0);
      sf::Vector2f end = text.findCharacterPos(count);
      textWidth = end.x - start.x;
    }

    float circleDiameter = 2.f * c.getRadius();

    if (textWidth > circleDiameter) {
      return "Name too long to fit in circle";
    }
  }
  container.push_back(c);
  return "";
}

void CircleContainer::delCircle(const std::string &circleName) {
  std::erase_if(container,
                [&](Circle &c) { return c.getName() == circleName; });
}

int CircleContainer::getSize() const { return container.size(); }

std::string CircleContainer::circlesToShape(sf::RenderWindow &w) {
  sf::CircleShape shape;

  static sf::Font font;
  static bool loaded = font.openFromFile("../resources/OpenSans.ttf");
  if (!loaded) {
    return "Can't open font file!";
  }
  sf::Text text(font);

  for (const auto &c : container) {
    shape.setRadius(c.getRadius());
    shape.setPointCount(100);
    shape.setFillColor(sf::Color(c.getRColor(), c.getGColor(), c.getBColor()));
    shape.setOrigin({c.getRadius(), c.getRadius()});
    shape.setPosition({c.getXPos(), c.getYPos()});

    text.setString(c.getName());
    text.setCharacterSize((int)(0.5 * c.getRadius()));
    if (c.getRColor() < 80 && c.getGColor() < 80 and c.getBColor() < 80) {
      text.setFillColor(sf::Color::White);
    }
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f textPos = textBounds.position;
    sf::Vector2f textSize = textBounds.size;

    // Calcular posición centrada respecto al círculo
    sf::Vector2f pos = {c.getXPos() - textSize.x / 2.f - textPos.x,
                        c.getYPos() - textSize.y / 2.f - textPos.y};

    text.setPosition(pos);

    w.draw(shape);
    w.draw(text);
  }
  return "";
}
