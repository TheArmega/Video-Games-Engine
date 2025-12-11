#include "core/Window.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>

// Constructor
Window::Window(std::string _name, unsigned int _width, unsigned int _height,
               unsigned int _fps)
    : name(_name), width(_width), height(_height), fps(_fps),
      sfWindow(sf::VideoMode(sf::Vector2u(_width, _height)), _name) {
  sfWindow.setFramerateLimit(_fps);
  if (!font.openFromFile("../assets/fonts/DynaPuff-Font.ttf"))
    std::cerr << "Can't load font." << std::endl;
}

// Setters
void Window::setWindow(sf::RenderWindow *w) { sfWindow = std::move(*w); }
void Window::setName(std::string n) { name = n; }
void Window::setWidth(unsigned int w) { width = w; }
void Window::setHeight(unsigned int h) { height = h; }
void Window::setFps(unsigned int f) { fps = f; }

// Getters
const sf::RenderWindow &Window::getSfWindow() const { return sfWindow; }
sf::RenderWindow &Window::getSfWindow() { return sfWindow; }
std::string Window::getName() { return name; }
unsigned int Window::getWidth() { return width; }
unsigned int Window::getHeight() { return height; }
unsigned int Window::getFps() { return fps; }

bool Window::checkWindow() {
  if (!ImGui::SFML::Init(sfWindow)) {
    std::cerr << "Can't create ImGui-SFML instance.";
    return false;
  }
  return true;
}

void Window::drawText(std::string t, unsigned int size, sf::Color color,
                      Vec2 pos) {
  sf::Text text(font);
  text.setString(t);
  text.setCharacterSize(size);
  text.setFillColor(color);
  text.setOrigin({pos.x, pos.y});
  text.setPosition({pos.x, pos.y});
  sfWindow.draw(text);
}
