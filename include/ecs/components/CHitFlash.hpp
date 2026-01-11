#include "ecs/core/Component.h"

class CHitFlash : public Component {

public:
  float timer = 0.f;
  float duration = 0.1f;

  CHitFlash() {}
  CHitFlash(float _duration) : duration(_duration) {}
};
