#include "ecs/core/Component.h"

class CInput : public Component {
public:
  bool up = false;
  bool down = false;
  bool right = false;
  bool left = false;
  bool shoot = false;

  CInput() {}
};
