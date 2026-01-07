#include "ecs/core/Component.h"
#include <SFML/Graphics.hpp>

class CShape : public Component {
public:
  sf::CircleShape shape;
  unsigned int points = 30;
  float radius = 10;
  sf::Color color = sf::Color::Red;

  CShape() {}

  CShape(unsigned int _points, float _radius, sf::Color _color)
      : points(_points), radius(_radius), color(_color) {
    shape.setPointCount(points);
    shape.setRadius(radius);
    shape.setFillColor(color);
    // shape.setOrigin({shape.getRadius(), shape.getRadius()});
  }

  CShape(float _radius, sf::Color _color) : radius(_radius), color(_color) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    // shape.setOrigin({shape.getRadius(), shape.getRadius()});
  }
};
