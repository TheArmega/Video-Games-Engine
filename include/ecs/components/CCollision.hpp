#include "ecs/core/Component.h"
#include <cstddef>

class CCollision : public Component {

public:
  size_t otherId;
  CCollision() {}
  CCollision(size_t _otherId) : otherId(_otherId) {}
};
