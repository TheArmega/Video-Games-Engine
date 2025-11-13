/**
 * @file physicsEngine.cpp
 * @brief PhysicsEngine class implementation
 * @ingroup CircleModule
 *
 * Implements the PhysicsEngine class constructor, with several methods
 */

#include "circleContainer.h"
#include "physicsEngine.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

const unsigned int WIDTH = 1440;
const unsigned int HEIGHT = 1080;
const int FPS = 60;
bool keepPushingMouseButton = false;
const float FORCE_SCALE = 0.5f;
const float DAMPING_COEFFICIENT = 5.f;
const float e = 0.8;

// ======================
// Constructor
// ======================
PhysicsEngine::PhysicsEngine(std::string _name, Circle *_activeCircle)
    : name(_name), activeCircle(_activeCircle) {}

// ======================
// Setters
// ======================
void PhysicsEngine::setName(std::string n) { name = n; }
void PhysicsEngine::setActiveCircle(Circle *c) { activeCircle = c; }

// ======================
// Getters
// ======================
std::string PhysicsEngine::getName() const { return name; }
Circle PhysicsEngine::getActiveCircle() const { return *activeCircle; }

// ======================
// Methods
// ======================
void PhysicsEngine::applyFrictionForce(Circle &c) {
  float factor = exp(-(DAMPING_COEFFICIENT / c.getMass() * 1 / FPS));
  c.setXVel(c.getXVel() * factor);
  c.setYVel(c.getYVel() * factor);
}

void PhysicsEngine::updateCirclesState(CircleContainer &container) {

  float x, y, vx, vy, r;

  for (auto &c : container.getContainer()) {

    applyFrictionForce(c);
    computeCollisionsBetweenCircles(container);

    float x = c.getXPos();
    float y = c.getYPos();
    float vx = c.getXVel();
    float vy = c.getYVel();
    float r = c.getRadius();

    if (vx != 0 || vy != 0) {
      x += vx;
      y += vy;

      if (x + r >= WIDTH || x - r <= 0) {
        vx = -vx;
        x = std::clamp(x, r, static_cast<float>(WIDTH) - r);
      }

      if (y + r >= HEIGHT || y - r <= 0) {
        vy = -vy;
        y = std::clamp(y, r, static_cast<float>(HEIGHT) - r);
      }

      c.setXPos(x);
      c.setYPos(y);
      c.setXVel(vx);
      c.setYVel(vy);
    }
  }
}

sf::Vector2f PhysicsEngine::getMousePoint(sf::RenderWindow &w) {
  sf::Vector2i mousePointer = sf::Mouse::getPosition(w);
  return sf::Vector2f{static_cast<float>(mousePointer.x),
                      static_cast<float>(mousePointer.y)};
}

bool PhysicsEngine::pointInCircleArea(const Circle &c, const sf::Vector2f &p) {
  float Dx = p.x - c.getXPos();
  float Dy = p.y - c.getYPos();
  float r = c.getRadius();

  return (Dx * Dx + Dy * Dy < r * r);
}

bool PhysicsEngine::circleInWindowArea(const Circle &c) {
  sf::Vector2f C = {c.getXPos(), c.getYPos()};
  float r = c.getRadius();

  if (0 <= C.x - r && WIDTH >= C.x + r && 0 <= C.y - r && HEIGHT >= C.y + r) {
    return true;
  } else
    return false;
}

std::optional<sf::Vector2f>
PhysicsEngine::getIntersectionPoint(const Circle c, const sf::Vector2f p) {

  if (!pointInCircleArea(c, p)) {
    sf::Vector2f Cp = {c.getXPos(), c.getYPos()};
    float r = c.getRadius();
    sf::Vector2f v = {p.x - Cp.x, p.y - Cp.y};

    float d = std::sqrt(v.x * v.x + v.y * v.y);
    float t = r / d;

    return sf::Vector2f{Cp.x + t * v.x, Cp.y + t * v.y};
  }

  return std::nullopt;
}

void PhysicsEngine::drawLineWithMouse(sf::RenderWindow &w,
                                      CircleContainer &container) {

  sf::Vector2f p = getMousePoint(w);

  for (auto &c : container.getContainer()) {

    bool inArea = pointInCircleArea(c, p);

    if (inArea) {
      keepPushingMouseButton = true;
      if (activeCircle == nullptr)
        activeCircle = &c;
      break;
    }
  }

  if (keepPushingMouseButton || activeCircle != nullptr) {

    auto IpOpt = getIntersectionPoint(*activeCircle, p);

    if (IpOpt.has_value()) {
      const auto &Ip = IpOpt.value();
      std::array line = {sf::Vertex{sf::Vector2f(Ip.x, Ip.y)},
                         sf::Vertex{sf::Vector2f(p.x, p.y)}};

      w.draw(line.data(), 2, sf::PrimitiveType::Lines);
    }
  }
}

void PhysicsEngine::pushCircleWhenRelease(sf::RenderWindow &w) {
  sf::Vector2f C = {activeCircle->getXPos(), activeCircle->getYPos()};
  float Cr = activeCircle->getRadius();

  sf::Vector2f P = getMousePoint(w);

  // Vector from C to P
  std::vector<float> v = {P.x - C.x, P.y - C.y};

  // Distance between C and P
  float distance = std::sqrt(v[0] * v[0] + v[1] * v[1]);

  // Compute intersection point between the circle and the vector CP
  auto IpOpt = getIntersectionPoint(*activeCircle, P);
  if (IpOpt.has_value()) {
    const auto &Ip = IpOpt.value();

    // Direction of the force vector (from mouse to circle border)
    sf::Vector2f direction = {Ip.x - P.x, Ip.y - P.y};
    // Magnitude of the direction vector
    float module =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    // Unit Vector
    sf::Vector2f unitVector = {direction.x / module, direction.y / module};

    // Vector of force
    float f = FORCE_SCALE * distance;
    sf::Vector2f forceVector = {unitVector.x * f, unitVector.y * f};

    // Vector of acceleration
    std::vector<float> acceVector = {forceVector.x / activeCircle->getMass(),
                                     forceVector.y / activeCircle->getMass()};

    activeCircle->setXVel(activeCircle->getXVel() + acceVector[0]);
    activeCircle->setYVel(activeCircle->getYVel() + acceVector[1]);
  }
}

float PhysicsEngine::dotProduct(const sf::Vector2f &v, const sf::Vector2f &_v) {
  return v.x * _v.x + v.y * _v.y;
}

float PhysicsEngine::distanceBetweenCircles(const Circle &c, const Circle &_c) {
  float Dx = c.getXPos() - _c.getXPos();
  float Dy = c.getYPos() - _c.getYPos();
  return sqrt(Dx * Dx + Dy * Dy);
}

bool PhysicsEngine::circlesCollide(const Circle &c, const Circle &_c) {
  if (distanceBetweenCircles(c, _c) <= c.getRadius() + _c.getRadius()) {
    return true;
  } else
    return false;
}

sf::Vector2f PhysicsEngine::computeDirectionCollisionVector(const Circle &c,
                                                            const Circle &_c) {
  float x = c.getXPos() - _c.getXPos();
  float y = c.getYPos() - _c.getYPos();
  float d = distanceBetweenCircles(c, _c);

  return {x / d, y / d};
}

sf::Vector2f PhysicsEngine::computeRelativeVelocity(const Circle &c,
                                                    const Circle &_c) {
  float xv = c.getXVel() - _c.getXVel();
  float yv = c.getYVel() - _c.getYVel();
  return {xv, yv};
}

void PhysicsEngine::computeCollisionsBetweenCircles(
    CircleContainer &container) {

  std::vector<Circle> &circles = container.getContainer();
  int size = container.getSize();
  sf::Vector2f direction;
  sf::Vector2f relative_vel;

  for (Circle &c : circles) {
    for (Circle &_c : circles) {
      if (circlesCollide(c, _c) && c.getName() != _c.getName()) {
        direction = computeDirectionCollisionVector(c, _c);
        relative_vel = computeRelativeVelocity(c, _c);

        float vrel_n = dotProduct(relative_vel, direction);
        if (vrel_n > 0)
          continue; // se están separando, no hay choque

        float j = -(1 + e) * vrel_n / (1 / c.getMass() + 1 / _c.getMass());

        c.setXVel(c.getXVel() + (j / c.getMass()) * direction.x);
        c.setYVel(c.getYVel() + (j / c.getMass()) * direction.y);

        _c.setXVel(_c.getXVel() - (j / _c.getMass()) * direction.x);
        _c.setYVel(_c.getYVel() - (j / _c.getMass()) * direction.y);

        float overlap =
            (c.getRadius() + _c.getRadius()) - distanceBetweenCircles(c, _c);
        if (overlap > 0) {
          float correctionFactor = 0.5f;
          c.setXPos(c.getXPos() + correctionFactor * overlap * direction.x);
          c.setYPos(c.getYPos() + correctionFactor * overlap * direction.y);

          _c.setXPos(_c.getXPos() - correctionFactor * overlap * direction.x);
          _c.setYPos(_c.getYPos() - correctionFactor * overlap * direction.y);
        }
      }
    }
  }
}
