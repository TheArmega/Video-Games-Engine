#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <vector>

class Circle {
private:
  std::string name;
  bool render;
  float radius;
  float mass;
  float xVel, yVel;
  int rColor, gColor, bColor;

public:
  Circle(std::string _name = "circle", bool _render = true,
         float _radius = 1.0f, float _mass = 1.0f, float _xVel = 1.0f,
         float _yVel = 1.0f, int _rColor = 255, int _gColor = 255,
         int _bColor = 255);

  // Setters
  void setName(std::string n);
  void setRender(bool r);
  void setRadius(float r);
  void setMass(float m);
  void setXVel(float x);
  void setYVel(float y);
  void setRColor(int r);
  void setGColor(int g);
  void setBColor(int b);

  // Getters
  std::string getName() const;
  bool getRender() const;
  float getRadius() const;
  float getMass() const;
  float getXVel() const;
  float getYVel() const;
  int getRColor() const;
  int getGColor() const;
  int getBColor() const;
};

#endif // CIRCLE_H
