#include "ecs/core/Entity.h"
#include "ecs/systems/PlayerShootSystem.h"
#include "utils/Vec2.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

constexpr float BULLET_SPEED = 600.f;

void PlayerShootSystem::update(EntityManager &em, sf::Window &w) {

  for (auto &e : em.getEntities()) {

    if (!e->has<CInput>() || !e->has<CTransform>())
      continue;

    auto &transform = e->get<CTransform>();
    auto &input = e->get<CInput>();

    if (input.shoot) {

      Vec2 c = transform.pos;
      float r = e->get<CShape>().radius;

      Vec2 p = {float(sf::Mouse::getPosition(w).x),
                float(sf::Mouse::getPosition(w).y)};

      Vec2 v = p - c;
      float n = std::sqrt(v.x * v.x + v.y * v.y);

      // Calculate the intersection point between the circle and the direction
      // vector
      Vec2 iP = c + ((v / n) * r);

      // Create the bullet entity
      auto bullet = em.addEntity("Bullet");
      bullet->add<CShape>(10, sf::Color::White);
      bullet->add<CTransform>(Vec2(iP.x, iP.y), Vec2(0, 0), Vec2(10, 10));
      bullet->add<CLifeSpan>(100);

      // Give the bullet a velocity acording to it's direction
      auto &transform = bullet->get<CTransform>();
      Vec2 dir = v / n;
      transform.velocity = dir * BULLET_SPEED;

      input.shoot = false;
    }
  }
}
