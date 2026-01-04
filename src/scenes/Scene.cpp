#include "ecs/core/EntityManager.h"
#include "scenes/Scene.h"
#include "scenes/SceneCommand.h"
#include <SFML/Graphics/RenderWindow.hpp>

// Constructor
Scene::Scene(const std::string _name, EntityManager *_entityManager)
    : name(_name), entityManager(_entityManager) {}

// Getters
std::string Scene::getName() { return name; }

// Virtual Methods
void Scene::init() {}
void Scene::update() {}
void Scene::render(sf::RenderWindow &w) {}
void Scene::cleanUp() {}
void Scene::handleEvent(const sf::Event &event) {}

SceneCommand Scene::getCommand() const { return command; }
void Scene::clearCommand() { command = SceneCommand::None; }
