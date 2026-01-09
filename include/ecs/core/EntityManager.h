#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "ecs/core/Entity.h"
#include <map>
#include <memory>
#include <string>

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager {
private:
  EntityVec m_entities;
  EntityVec m_toAdd; // We need this in order to prevent iterator invalidation
                     // so this vector will save all the elements to add and add
                     // them at the very first frame of the next step
  EntityVec m_toDelete;
  EntityMap m_entityMap;
  size_t m_totalEntities = 0;

public:
  EntityManager() {};
  void update();
  std::shared_ptr<Entity> addEntity(const std::string &tag);
  EntityVec &getEntities(); // Return the vector with all entities
  EntityVec &getEntities(
      const std::string
          &tag); // Return the vector with all entities with a specific tag
  std::shared_ptr<Entity> getEntityById(const size_t id);
};

#endif // ENTITYMANAGER_H
