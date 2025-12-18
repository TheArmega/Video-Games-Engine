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
         const std::string hoveredTexturePath, Vec2 pos);

  // Getters
  std::string getName();

  // Methods
  // Draw the button in the window
  void draw(Window &w) const;

  // Update the state of the button
  void update(const Window &w);

  void handleEvent(const sf::Event &event, const Window &w);

  // A
  void setOnClick(std::function<void()> callback);
};

#endif // BUTTON_H
