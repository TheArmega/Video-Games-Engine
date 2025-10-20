#include "circleContainer.h"
#include <SFML/Graphics/CircleShape.hpp>

CircleContainer::CircleContainer(std::string _name) : name(_name) {}

void CircleContainer::setName(std::string n) { name = n; }

std::string CircleContainer::getName() const { return name; }

const std::unordered_map<std::string, sf::CircleShape> &
CircleContainer::getContainer() const {
  return container;
}

void CircleContainer::addCircle(const Circle &c) {
  sf::CircleShape shape(c.getRadius());
  shape.setFillColor(sf::Color(c.getRColor(), c.getGColor(), c.getBColor()));
  shape.setOrigin({c.getRadius(), c.getRadius()});
  shape.setPosition({c.getXPos(), c.getYPos()});

  container[c.getName()] = shape;
}

void CircleContainer::delCircle(const std::string &circleName) {
  container.erase(circleName);
}

int CircleContainer::getSize() const {
  return static_cast<int>(container.size());
}
