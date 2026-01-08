#include "ecs/core/Component.h"

class CLifeSpan : public Component {
public:
  int life = 100;
  CLifeSpan() {}
  CLifeSpan(int _life) : life(_life) {}
};
