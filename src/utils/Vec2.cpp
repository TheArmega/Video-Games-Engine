#include <iostream>

#include "utils/Vec2.h"

Vec2::Vec2() : x(0), y(0) {};
Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {};

void Vec2::print() { std::cout << x << " " << y << std::endl; }
