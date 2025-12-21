#ifndef TITLE_H
#define TITLE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#include "utils/Vec2.h"

class Title {
private:
  std::string name;
  sf::Texture texture;
  sf::Sprite sprite;

public:
  // Constructor
  Title(const std::string _name, const std::string texturePath, Vec2 pos,
        Vec2 scale);

  // Getters
  std::string getName();
  const sf::Sprite &getSprite() const;

  // Methods
};

#endif // TITLE_H
