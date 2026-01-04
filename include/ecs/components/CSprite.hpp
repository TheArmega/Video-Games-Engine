#include "ecs/core/Component.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

class CSprite : public Component {
public:
  sf::Texture texture;
  sf::Sprite sprite;
  CSprite() : sprite(texture) {};
  CSprite(const std::string &spriteRoute) : sprite(texture) {

    if (!texture.loadFromFile(spriteRoute)) {
      std::cerr << "Failed to load sprite texture: " << spriteRoute << "\n";
    }

    sprite = sf::Sprite(texture);
  }
};
