#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "utils/Vec2.h"

class Window {

private:
  sf::RenderWindow sfWindow;
  sf::Font font;
  std::string name = "General Window";
  unsigned int width = 1440;
  unsigned int height = 1080;
  unsigned int fps = 60;

public:
  // Constructor
  Window(std::string _name, unsigned int _width, unsigned int _height,
         unsigned int _fps);

  // Setters
  void setWindow(sf::RenderWindow *w);
  void setName(std::string n);
  void setWidth(unsigned int w);
  void setHeight(unsigned int h);
  void setFps(unsigned int f);

  // Getters
  const sf::RenderWindow &getSfWindow() const;
  sf::RenderWindow &getSfWindow();
  std::string getName();
  unsigned int getWidth();
  unsigned int getHeight();
  unsigned int getFps();

  // Check if the window has been created succesfully
  bool checkWindow();

  // Put a text in a given position in the window
  void drawText(std::string t, unsigned int size, sf::Color color, Vec2 pos);
};

#endif // WINDOW_H
