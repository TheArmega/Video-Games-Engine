#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class Button {
private:
  std::string name = "Generic Button";
  std::string staticTexture;
  std::string variableTexture;
  unsigned int xPos;
  unsigned int yPos;

public:
  // Constructor
  Button(std::string _name, std::string _staticTexture,
         std::string _variableTexture, unsigned int _xPos, unsigned int _yPos);

  // Setters
  void setName(std::string n);
  void setStaticTexture(std::string t);
  void setVariableTexture(std::string t);
  void setXPos(unsigned int x);
  void setYPos(unsigned int y);

  // Getters
  std::string getName();
  std::string getStaticTexture();
  std::string getVariableTexture();
  unsigned int getXPos();
  unsigned int getYPos();

  // Methods
  // Render the button in the window
  void render(sf::RenderWindow &w);
};

#endif // BUTTON_H
