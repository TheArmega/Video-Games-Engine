#include "core/Window.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>

// Constructor
Window::Window(std::string _name, unsigned int _width, unsigned int _height,
               unsigned int _fps)
    : width(_width), height(_height), fps(_fps),
      sfWindow(sf::VideoMode(sf::Vector2u(_width, _height)), _name) {
  sfWindow.setFramerateLimit(_fps);
}

// Setters
void Window::setWidth(unsigned int w) { width = w; }
void Window::setHeight(unsigned int h) { height = h; }
void Window::setFps(unsigned int f) { fps = f; }

// Getters
const sf::RenderWindow &Window::getSfWindow() const { return sfWindow; }
sf::RenderWindow &Window::getSfWindow() { return sfWindow; }
unsigned int Window::getWidth() { return width; }
unsigned int Window::getHeight() { return height; }
unsigned int Window::getFps() { return fps; }

// Methods
bool Window::checkWindow() {
  if (!ImGui::SFML::Init(sfWindow)) {
    std::cerr << "Can't create ImGui-SFML instance.";
    return false;
  }
  return true;
}

void Window::draw(const sf::Drawable &drawable) { sfWindow.draw(drawable); }

Vec2 Window::getMousePos() const {
  auto p = sf::Mouse::getPosition(sfWindow);

  Vec2 pos = {float(p.x), float(p.y)};
  return pos;
}
