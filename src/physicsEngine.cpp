/**
 * @file physicsEngine.cpp
 * @brief PhysicsEngine class implementation
 * @ingroup CircleModule
 *
 * Implements the PhysicsEngine class constructor, with several methods
 */

#include "physicsEngine.h"
#include <SFML/System/Vector2.hpp>

constexpr float FORCE_SCALE = 0.5f;

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

std::optional<sf::Vector2f>
PhysicsEngine::getIntersectionPoint(Circle c, sf::Vector2f p) {

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
                                      CircleContainer &container,
                                      bool &keepPushing) {

  sf::Vector2f p = getMousePoint(w);

  for (auto &c : container.getContainer()) {

    bool inArea = pointInCircleArea(c, p);

    if (inArea) {
      keepPushing = true;
      if (activeCircle == nullptr)
        activeCircle = &c;
      break;
    }
  }

  if (keepPushing || activeCircle != nullptr) {

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
    std::vector<float> direction = {Ip.x - P.x, Ip.y - P.y};
    // Magnitude of the direction vector
    float module =
        std::sqrt(direction[0] * direction[0] + direction[1] * direction[1]);
    // Unit Vector
    std::vector<float> unitVector = {direction[0] / module,
                                     direction[1] / module};

    // Vector of force
    float f = FORCE_SCALE * distance;
    std::vector<float> forceVector = {unitVector[0] * f, unitVector[1] * f};

    // Vector of acceleration
    std::vector<float> acceVector = {forceVector[0] / activeCircle->getMass(),
                                     forceVector[1] / activeCircle->getMass()};

    activeCircle->setXVel(activeCircle->getXVel() + acceVector[0]);
    activeCircle->setYVel(activeCircle->getYVel() + acceVector[1]);
  }
}
