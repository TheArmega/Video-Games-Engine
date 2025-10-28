/**
 * @file circleContainer.h
 * @author Jaime
 * @brief CircleContainer class declaration
 * @version 0.1
 * @date 23/10/25
 *
 * @defgroup CircleContainerModule CircleContainer Class
 * @brief Manages a collection of Circle objects and their SFML representations
 * @{
 */

#ifndef CIRCLECONTAINER_H
#define CIRCLECONTAINER_H

#include "circle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <string>
#include <vector>

/**
 * @class CircleContainer
 * @brief Manages a collection of Circle objects and their SFML shapes.
 *
 * This class allows adding, deleting, and managing multiple Circle objects
 * in a container, represented by SFML CircleShape objects.
 */
class CircleContainer {
private:
  std::string name = "container";     ///< Container name
  std::vector<Circle> container = {}; ///< Vector with cirles
  Circle *activeCircle = nullptr;
  float lineDistance = 0.f;

public:
  /**
   * @brief Constructs a new CircleContainer object
   * @param _name Name of the container (default "container")
   */
  CircleContainer(std::string _name = "container",
                  std::vector<Circle> _container = {},
                  Circle *_activeCircle = nullptr, float _lineDistance = 0.f);

  /// @name Setters
  /// @{
  void setName(std::string n);              ///< Sets the name of the container
  void setContainer(std::vector<Circle> c); ///< Sets the container
  void setActiveCircle(Circle *c);          ///< Sets active circle
  void setLineDistance(float d);            ///< Sets line distance
  /// @}

  /// @name Getters
  /// @{
  std::string getName() const; ///< Returns name of the container
  const std::vector<Circle> &getContainer() const; ///< Returns the container
  Circle *getActiveCircle() const;                 ///< Returns active circle
  float getLineDistance() const;                   ///< Returns line distance
  /// @}

  /// @name Methods
  /// @{
  /**
   * @brief Adds a Circle to the container
   * @param c Circle to add
   */
  void addCircle(const Circle &c);

  /**
   * @brief Deletes a Circle from the container by name
   * @param circleName Name of the Circle to delete
   */
  void delCircle(const std::string &circleName);

  /**
   * @brief Returns the number of Circles in the container
   * @return Number of Circles
   */
  int getSize() const;

  /**
   * @brief Returns a vector with the circles transformed to shapes's
   * @return Vector of shapes
   */
  void circlesToShape(sf::RenderWindow &w);

  /**
   * @brief Updates state of all circles, position, speed and check collisions
   */
  void updateCirclesState(int width, int height);

  /**
   * @brief Check if mouse pointer inside a circle
   */
  void clickOnCircle(sf::RenderWindow &w, bool &keepPushing);
};

#endif // CIRCLECONTAINER_H

/** @} */ // end of CircleContainerModule
