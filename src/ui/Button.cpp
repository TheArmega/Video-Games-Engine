#include "core/Window.h"
#include "ui/Button.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <utility>

// Constructor
Button::Button(const std::string _name, const std::string normalTexturePath,
               const std::string hoveredTexturePath, Vec2 pos, Vec2 scale)
    : name(_name), sprite(normalTexture) {
  if (!normalTexture.loadFromFile(normalTexturePath)) {
    std::cerr << "Failed to load button texture: " << normalTexturePath << '\n';
  }

  if (!hoveredTexture.loadFromFile(hoveredTexturePath)) {
    std::cerr << "Failed to load button texture: " << hoveredTexturePath
              << '\n';
  }

  sprite = sf::Sprite(normalTexture);
  sprite.setTexture(normalTexture);
  sprite.setPosition({pos.x, pos.y});
  sprite.setScale({scale.x, scale.y});
}

// Getters
std::string Button::getName() { return name; }
const sf::Sprite &Button::getSprite() const { return sprite; }

// Methods
void Button::handleEvent(const sf::Event &event, const Window &w) {
  if (const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>()) {

    if (mouse->button != sf::Mouse::Button::Left) {
      return;
    }

    Vec2 mousePos = w.getMousePos();
    if (sprite.getGlobalBounds().contains({mousePos.x, mousePos.y})) {
      if (onClick) {
        onClick();
      }
    }
  }
}

void Button::update(const Window &w) {
  Vec2 mouse = w.getMousePos();
  bool isHover = sprite.getGlobalBounds().contains({mouse.x, mouse.y});

  sprite.setTexture(isHover ? hoveredTexture : normalTexture);
}

void Button::setOnClick(std::function<void()> callback) {
  onClick = std::move(callback);
}

void Button::drawBoundingBox(Window &w) {
  sf::FloatRect bounds = sprite.getGlobalBounds();

  sf::RectangleShape boundingBox;
  boundingBox.setPosition({bounds.position.x, bounds.position.y});
  boundingBox.setSize({bounds.size.x, bounds.size.y});
  boundingBox.setFillColor(sf::Color::Transparent);
  boundingBox.setOutlineThickness(1.f);
  boundingBox.setOutlineColor(sf::Color::Red);

  w.draw(boundingBox);
}
