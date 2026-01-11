#include "ecs/core/Entity.h"
#include "ecs/systems/DisplayScoreSystem.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

void DisplayScoreSystem::update(EntityManager &em, Window &w) {
  for (auto &e : em.getEntities()) {
    if (!e->has<CScore>())
      continue;

    auto &score = e->get<CScore>();

    sf::Font font("../assets/fonts/DynaPuff-Font.ttf");
    sf::Text scoreText(font);
    scoreText.setString("Score : " + std::to_string(int(score.score)));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10, 10});

    w.draw(scoreText);
  }
}
