#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>
#include <string>
#include <tuple>
#include <utility>

#include "ecs/components/CCollision.hpp"
#include "ecs/components/CDamage.hpp"
#include "ecs/components/CHitFlash.hpp"
#include "ecs/components/CInput.hpp"
#include "ecs/components/CLife.hpp"
#include "ecs/components/CLifeSpan.hpp"
#include "ecs/components/COwner.hpp"
#include "ecs/components/CRotation.hpp"
#include "ecs/components/CScore.hpp"
#include "ecs/components/CShape.hpp"
#include "ecs/components/CSprite.hpp"
#include "ecs/components/CTransform.hpp"
#include "ecs/components/CWobble.hpp"

using ComponentTuple =
    std::tuple<CTransform, CSprite, CShape, CLife, CInput, CLifeSpan, CDamage,
               CCollision, CWobble, CHitFlash, CRotation, CScore, COwner>;

class Entity {
private:
  ComponentTuple m_components;
  bool m_alive = true;
  std::string m_tag = "default";
  size_t m_id = 0;

public:
  Entity(std::string tag, size_t id) : m_tag(std::move(tag)), m_id(id) {}

  template <typename T, typename... TArgs> T &add(TArgs &&...args) {
    auto &component = std::get<T>(m_components);
    component = T(std::forward<TArgs>(args)...);
    component.exists = true;
    return component;
  }

  template <typename T> T &get() { return std::get<T>(m_components); }

  template <typename T> const T &get() const {
    return std::get<T>(m_components);
  }

  template <typename T> bool has() const {
    return std::get<T>(m_components).exists;
  }

  template <typename T> void remove() { std::get<T>(m_components) = T{}; }

  size_t id() const { return m_id; }
  bool isAlive() const { return m_alive; }
  void destroy() { m_alive = false; }
  const std::string &tag() const { return m_tag; }
};

#endif
