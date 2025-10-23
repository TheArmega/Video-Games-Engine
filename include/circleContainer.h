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
#include <string>
#include <unordered_map>
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
  std::string name; ///< Name of the container
  std::unordered_map<std::string, sf::CircleShape>
      container; ///< Map of CircleShapes by name

public:
  /**
   * @brief Constructs a new CircleContainer object
   * @param _name Name of the container (default "container")
   */
  CircleContainer(
      std::string _name = "container",
      std::unordered_map<std::string, sf::CircleShape> _container = {});

  /// @name Setters
  /// @{
  void setName(std::string n); ///< Sets the container's name
  /// @}

  /// @name Getters
  /// @{
  std::string getName() const; ///< Returns the container's name
  const std::unordered_map<std::string, sf::CircleShape> &
  getContainer() const; ///< Returns the container
  /// @}

  /// @name Methods
  /// @{
  /**
   * @brief Adds a Circle to the container
   * @param c Circle to add
   */
  void addCircle(const Circle &c);

  /**
   * @brief Adds multiple Circles from a vector
   * @param v Vector of Circle objects to add
   */
  void addCirclesFromVector(const std::vector<Circle> v);

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
  /// @}
};

#endif // CIRCLECONTAINER_H

/** @} */ // end of CircleContainerModule
