#include "circle.h"

Circle::Circle(std::string _name, bool _render, float _radius, float _mass,
               float _xVel, float _yVel, int _rColor, int _gColor, int _bColor)
    : name(_name), render(_render), radius(_radius), mass(_mass), xVel(_xVel),
      yVel(_yVel), rColor(_rColor), gColor(_gColor), bColor(_bColor) {}

// Setters
void Circle::setName(std::string n) { name = n; }
void Circle::setRender(bool b) { render = b; }
void Circle::setRadius(float r) { radius = r; }
void Circle::setMass(float m) { mass = m; }
void Circle::setXVel(float v) { xVel = v; }
void Circle::setYVel(float v) { yVel = v; }
void Circle::setRColor(int r) { rColor = r; }
void Circle::setGColor(int g) { gColor = g; }
void Circle::setBColor(int b) { bColor = b; }

// Getters
std::string Circle::getName() const { return name; }
bool Circle::getRender() const { return render; }
float Circle::getRadius() const { return radius; }
float Circle::getMass() const { return mass; }
float Circle::getXVel() const { return xVel; }
float Circle::getYVel() const { return yVel; }
int Circle::getRColor() const { return rColor; }
int Circle::getGColor() const { return gColor; }
int Circle::getBColor() const { return bColor; }
