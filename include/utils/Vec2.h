#ifndef VEC2_H
#define VEC2_H

class Vec2 {

public:
  float x = 0;
  float y = 0;

  Vec2();
  Vec2(float _x, float _y);

  void add(Vec2 v);

  Vec2 operator+(Vec2 v);
  Vec2 operator-(Vec2 v);
  Vec2 operator*(Vec2 v);
  Vec2 operator*(float d);
  Vec2 operator/(Vec2 v);
  Vec2 operator/(float d);

  float module();
  Vec2 normalized();

  void print();
};

#endif // VEC2_H
