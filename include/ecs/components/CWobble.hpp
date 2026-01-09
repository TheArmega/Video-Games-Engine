#include "ecs/core/Component.h"

class CWobble : public Component {
public:
  float phase = 0.f;
  float frequency = .2f;
  float amplitude = 5.f;

  CWobble() {}
  CWobble(float _phase, float _frequency, float _amplitude)
      : phase(_phase), frequency(_frequency), amplitude(_amplitude) {}
};
