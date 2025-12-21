#include "core/ImGuiLayer.h"
#include <SFML/Graphics/RenderWindow.hpp>

// Constructor
ImGuiLayer::ImGuiLayer(Window &_relatedWindow, std::string _name,
                       unsigned int _width, unsigned int _height,
                       unsigned int _xPos, unsigned int _yPos)
    : relatedWindow(_relatedWindow), name(_name), width(_width),
      height(_height), xPos(_xPos), yPos(_yPos) {}

// Setters
void ImGuiLayer::setFont(sf::Font f) { font = f; }
void ImGuiLayer::setName(std::string n) { name = n; }
void ImGuiLayer::setWidth(unsigned int w) { width = w; }
void ImGuiLayer::setHeight(unsigned int h) { height = h; }
void ImGuiLayer::setXPos(unsigned int x) { xPos = x; }
void ImGuiLayer::setYPos(unsigned int y) { yPos = y; }

// Getters
const Window &ImGuiLayer::getRelatedWindow() const { return relatedWindow; }
Window &ImGuiLayer::getRelatedWindow() { return relatedWindow; }
sf::Font ImGuiLayer::getFont() { return font; }
std::string ImGuiLayer::getName() { return name; }
unsigned int ImGuiLayer::getWidth() { return width; }
unsigned int ImGuiLayer::getHeight() { return height; }
unsigned int ImGuiLayer::getXPos() { return xPos; }
unsigned int ImGuiLayer::getYPos() { return yPos; }
