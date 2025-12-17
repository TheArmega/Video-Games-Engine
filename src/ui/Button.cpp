#include "ui/Button.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

// Constructor
Button::Button(std::string _name, std::string _staticTexture,
               std::string _variableTexture, unsigned int _xPos,
               unsigned int _yPos)
    : name(_name), staticTexture(_staticTexture),
      variableTexture(_variableTexture), xPos(_xPos), yPos(_yPos) {}

// Setters
void Button::setName(std::string n) { name = n; }
void Button::setStaticTexture(std::string t) { staticTexture = t; }
void Button::setVariableTexture(std::string t) { variableTexture = t; }
void Button::setXPos(unsigned int x) { xPos = x; }
void Button::setYPos(unsigned int y) { yPos = y; }

// Getters
std::string Button::getName() { return name; }
std::string Button::getStaticTexture() { return staticTexture; }
std::string Button::getVariableTexture() { return variableTexture; }
unsigned int Button::getXPos() { return xPos; }
unsigned int Button::getYPos() { return yPos; }

// Methods
void Button::render(sf::RenderWindow &w) {
  const sf::Texture texture(staticTexture);

  sf::Sprite sprite(texture);
  sprite.setPosition({float(xPos), float(yPos)});
  w.draw(sprite);
}
