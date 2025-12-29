#include "ecs/core/Component.h"
#include <SFML/Graphics.hpp>

class CShape : public Component {
public:
  sf::CircleShape shape;
  CShape() {}
};
