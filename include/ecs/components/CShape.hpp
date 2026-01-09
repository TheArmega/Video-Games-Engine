#include "ecs/core/Component.h"
#include <SFML/Graphics.hpp>

class CShape : public Component {
public:
  sf::CircleShape shape;
  unsigned int points = 30;
  float radius = 10;
  sf::Color fillColor = sf::Color::Red;
  sf::Color outLineColor = sf::Color::White;
  float outLineThickness = 5.f;

  CShape() {}

  CShape(unsigned int _points, float _radius, sf::Color _fillColor,
         sf::Color _outLineColor, float _outLineThickness)
      : points(_points), radius(_radius), fillColor(_fillColor),
        outLineColor(_outLineColor), outLineThickness(_outLineThickness) {
    shape.setPointCount(points);
    shape.setRadius(radius);
    shape.setFillColor(fillColor);
    shape.setOutlineColor(outLineColor);
    shape.setOutlineThickness(outLineThickness);
    shape.setOrigin({shape.getRadius(), shape.getRadius()});
  }

  CShape(unsigned int _points, float _radius, sf::Color _fillColor)
      : points(_points), radius(_radius), fillColor(_fillColor) {
    shape.setPointCount(points);
    shape.setRadius(radius);
    shape.setFillColor(fillColor);
    shape.setOutlineColor(outLineColor);
    shape.setOutlineThickness(outLineThickness);
    shape.setOrigin({shape.getRadius(), shape.getRadius()});
  }

  CShape(float _radius, sf::Color _fillColor)
      : radius(_radius), fillColor(_fillColor) {
    shape.setPointCount(points);
    shape.setRadius(radius);
    shape.setFillColor(fillColor);
    shape.setOutlineColor(outLineColor);
    shape.setOutlineThickness(outLineThickness);
    shape.setOrigin({shape.getRadius(), shape.getRadius()});
  }
};
