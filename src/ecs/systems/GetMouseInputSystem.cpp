#include "ecs/core/Entity.h"
#include "ecs/systems/GetMouseInputSystem.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

void GetMouseInputSystem::update(EntityManager &em, const sf::Event &event) {
  if (!event.is<sf::Event::MouseButtonPressed>() &&
      !event.is<sf::Event::MouseButtonReleased>())
    return;

  const bool pressed = event.is<sf::Event::MouseButtonPressed>();

  sf::Mouse::Button button =
      pressed ? event.getIf<sf::Event::MouseButtonPressed>()->button
              : event.getIf<sf::Event::MouseButtonReleased>()->button;

  for (auto &e : em.getEntities()) {
    if (!e->has<CInput>())
      continue;

    auto &input = e->get<CInput>();

    if (pressed && !input.lock_click && (button == sf::Mouse::Button::Left)) {
      input.shoot = true;
      input.lock_click = true;
    }

    if (!pressed) {
      input.shoot = false;
      input.lock_click = false;
    }
  }
}
