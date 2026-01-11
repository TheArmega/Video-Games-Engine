#include "ecs/core/Component.h"
#include <cstddef>

class COwner : public Component {

public:
  size_t owner;
  COwner() {}
  COwner(size_t _owner) : owner(_owner) {}
};
