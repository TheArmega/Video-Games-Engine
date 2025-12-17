#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "core/Window.h"

class ImGuiLayer {
private:
  Window &relatedWindow;
  sf::Font font;
  std::string name = "ImGui Window";
  unsigned int width = 250;
  unsigned int height = 250;
  unsigned int xPos = 100;
  unsigned int yPos = 100;

public:
  // Constructor
  ImGuiLayer(Window &_relatedWindow, std::string _name, unsigned int _width,
             unsigned int height, unsigned int _xPos, unsigned int _yPos);

  // Setters
  void setRelatedWindow(Window w);
  void setFont(sf::Font f);
  void setName(std::string n);
  void setWidth(unsigned int w);
  void setHeight(unsigned int h);
  void setXPos(unsigned int x);
  void setYPos(unsigned int y);

  // Getters
  const Window &getRelatedWindow() const;
  Window &getRelatedWindow();
  sf::Font getFont();
  std::string getName();
  unsigned int getWidth();
  unsigned int getHeight();
  unsigned int getXPos();
  unsigned int getYPos();
};

#endif // IMGUILAYER_H
