#include "ecs/core/Component.h"

class CLife : public Component {
public:
  float hp = 100;
  CLife() {};
  CLife(float _hp) : hp(_hp) {}
};
