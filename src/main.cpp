#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

int main() {

  int const width = 1440;
  int const height = 1080;
  sf::RenderWindow window(sf::VideoMode({width, height}), "VideoGameEngine");

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color(138, 206, 0));
  shape.setOrigin({shape.getRadius(), shape.getRadius()});
  shape.setPosition({float(width) / 2, float(height) / 2});

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }
    window.clear();
    window.draw(shape);
    window.display();
  }
}
