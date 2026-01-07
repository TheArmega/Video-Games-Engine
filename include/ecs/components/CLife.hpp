#include "ecs/core/Component.h"

class CLife : public Component {
public:
  unsigned int hp = 100;
  CLife() {};
  CLife(unsigned int _hp) : hp(_hp) {}
};
