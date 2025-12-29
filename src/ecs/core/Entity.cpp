#include "ecs/core/Entity.h"

// Constructor
Entity::Entity(std::string _m_tag, size_t _m_id) : m_tag(_m_tag), m_id(_m_id) {}

// Methods
template <typename T, typename... TArgs> T &Entity::add(TArgs &&...mArgs) {
  auto &component = get<T>();
  component = T(std::forward<TArgs>(mArgs)...);
  component.exists = true;
  return component;
}

template <typename T> T &Entity::get() { return std::get<T>(m_components); }
template <typename T> const T &Entity::get() const {
  return std::get<T>(m_components);
}

template <typename T> bool Entity::has() const { return std::get<T>().exists; }
template <typename T> void Entity::remove() { get<T>() = T(); }
