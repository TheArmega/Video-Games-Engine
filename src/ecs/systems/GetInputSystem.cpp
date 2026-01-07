
#include "ecs/core/EntityManager.h"
#include "ecs/systems/GetInputSystem.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

void GetInputSystem::update(EntityManager &em, const sf::Event &event) {

  if (!event.is<sf::Event::KeyPressed>() &&
      !event.is<sf::Event::KeyReleased>()) {
    return;
  }

  const bool pressed = event.is<sf::Event::KeyPressed>();

  sf::Keyboard::Key key = pressed ? event.getIf<sf::Event::KeyPressed>()->code
                                  : event.getIf<sf::Event::KeyReleased>()->code;

  for (auto &e : em.getEntities()) {
    if (!e->has<CInput>())
      continue;

    auto &input = e->get<CInput>();

    if (key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::Up)
      input.up = pressed;
    else if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down)
      input.down = pressed;
    else if (key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::Left)
      input.left = pressed;
    else if (key == sf::Keyboard::Key::D || key == sf::Keyboard::Key::Right)
      input.right = pressed;
  }
}
