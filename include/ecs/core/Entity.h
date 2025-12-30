#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>
#include <string>
#include <tuple>

#include "Component.h"
#include "ecs/components/CShape.hpp"
#include "ecs/components/CTransform.hpp"

using ComponentTuple = std::tuple<CTransform, CShape>;

class Entity {
private:
  std::tuple<Component> m_components;
  bool m_alive = true;
  std::string m_tag = "default";
  size_t m_id = 0;

public:
  Entity(std::string _m_tag, size_t _m_id);
  template <typename T, typename... TArgs> T &add(TArgs &&...args);
  template <typename T> T &get();
  template <typename T> const T &get() const;
  template <typename T> bool has() const;
  template <typename T> void remove();
  size_t id();
  bool isAlive() const;
  void destroy();
  const std::string &tag() const;
};

#endif // ENTITY_H
