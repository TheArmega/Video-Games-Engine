#include "ui/Title.h"

// Constructor
Title::Title(const std::string _name, const std::string texturePath, Vec2 pos,
             Vec2 scale)
    : name(_name), sprite(texture) {
  if (!texture.loadFromFile(texturePath))
    std::cout << "Failed to load title texture: " << texturePath << std::endl;

  sprite = sf::Sprite(texture);
  sprite.setTexture(texture);
  sprite.setPosition({pos.x, pos.y});
  sprite.setScale({scale.x, scale.y});
}

// Getters
std::string Title::getName() { return name; }
const sf::Sprite &Title::getSprite() const { return sprite; }

// Methods
