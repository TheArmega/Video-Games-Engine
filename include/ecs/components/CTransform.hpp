#include "ecs/core/Component.h"
#include "utils/Vec2.h"

class CTransform : public Component {
public:
  Vec2 pos = {0, 0};
  Vec2 velocity = {0, 0};
  Vec2 speed = {0, 0};
  CTransform() {}
  CTransform(const Vec2 &_pos, const Vec2 &_speed) : pos(_pos), speed(_speed) {}
};
