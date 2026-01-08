#include "utils/Geometry.h"
#include <cmath>

bool Geometry::pointInCircle(Vec2 p, Vec2 c, float r) {
  int dx = std::abs(p.x - c.x);
  int dy = std::abs(p.y - c.y);
  return (dx * dx + dy * dy <= r * r);
}
