#include "ecs/core/Component.h"

class CDamage : public Component {

public:
  float damage = 10;
  CDamage() {}
  CDamage(float _damage) : damage(_damage) {};
};
