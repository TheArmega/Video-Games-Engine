#include "ecs/core/EntityManager.h"
#include <algorithm>
#include <memory>

void EntityManager::update() {
  for (auto e : m_toAdd) {
    m_entities.push_back(e);
    m_entityMap[e->tag()].push_back(e);
  }

  m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
                                  [](const std::shared_ptr<Entity> &e) {
                                    return !e->isAlive();
                                  }),
                   m_entities.end());

  for (auto it = m_entityMap.begin(); it != m_entityMap.end();) {

    auto vec = it->second;

    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](const std::shared_ptr<Entity> &e) {
                               return !e->isAlive();
                             }),
              vec.end());

    if (vec.empty()) {
      it = m_entityMap.erase(it);
    } else
      it++;
  }

  m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
  auto e = std::shared_ptr<Entity>(
      new Entity(tag, m_totalEntities++)); // Create the entity (only able to do
                                           // by the EntityManager)
  m_toAdd.push_back(e);
  return e;
}

EntityVec &EntityManager::getEntities() { return m_entities; }
EntityVec &EntityManager::getEntities(const std::string &tag) {
  return m_entityMap[tag];
}
