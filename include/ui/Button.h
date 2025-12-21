#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <functional>
#include <iostream>
#include <string>

#include "utils/Vec2.h"

// Forward declaration
class Window;

class Button {
private:
  std::string name;
  sf::Texture normalTexture;
  sf::Texture hoveredTexture;
  sf::Sprite sprite;

  std::function<void()> onClick;
  bool hovered = false;

public:
  // Constructor
  Button(const std::string _name, const std::string normalTexturePath,
         const std::string hoveredTexturePath, Vec2 pos, Vec2 scale);

  // Getters
  std::string getName();
  const sf::Sprite &getSprite() const;

  // Methods
  // Update the state of the button
  void update(const Window &w);

  void handleEvent(const sf::Event &event, const Window &w);

  // Function that launches on click
  void setOnClick(std::function<void()> callback);

  void drawBoundingBox(Window &w);
};

#endif // BUTTON_H
