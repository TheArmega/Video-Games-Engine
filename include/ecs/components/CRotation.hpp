#include "ecs/core/Component.h"
#include <SFML/System/Angle.hpp>

class CRotation : public Component {

public:
  sf::Angle velocity = sf::degrees(5);
  CRotation() {}
  CRotation(float _velocity) { velocity = sf::degrees(_velocity); }
};
