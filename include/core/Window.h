#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <vector>

#include "ui/Button.h"
#include "utils/Vec2.h"

class Window {

private:
  sf::RenderWindow sfWindow;
  unsigned int width = 1440;
  unsigned int height = 1080;
  unsigned int fps = 60;

public:
  // Constructor
  Window(std::string _name, unsigned int _width, unsigned int _height,
         unsigned int _fps);

  // Setters
  void setWidth(unsigned int w);
  void setHeight(unsigned int h);
  void setFps(unsigned int f);

  // Getters
  const sf::RenderWindow &getSfWindow() const;
  sf::RenderWindow &getSfWindow();
  unsigned int getWidth();
  unsigned int getHeight();
  unsigned int getFps();

  // Draw a drawable object
  void draw(const sf::Drawable &drawable);

  // Get mouse position
  Vec2 getMousePos() const;
};

#endif // WINDOW_H
