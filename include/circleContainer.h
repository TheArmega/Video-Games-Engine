#ifndef CIRCLECONTAINER_H
#define CIRCLECONTAINER_H

#include "circle.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class CircleContainer {
private:
  std::string name;
  std::unordered_map<std::string, sf::CircleShape> container;

public:
  CircleContainer(std::string _name = "container");

  // Setters
  void setName(std::string n);

  // Getters
  std::string getName() const;
  const std::unordered_map<std::string, sf::CircleShape> &getContainer() const;

  // Methods
  void addCircle(const Circle &c);
  void delCircle(const std::string &circleName);
  int getSize() const;
};

#endif // CIRCLECONTAINER_H
