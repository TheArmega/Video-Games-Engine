#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "utils/Vec2.h"

class Geometry {

public:
  static bool pointInCircle(Vec2 p, Vec2 c, float r);
};

#endif // GEOMETRY_H
