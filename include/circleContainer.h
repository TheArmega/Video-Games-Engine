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

public:
  /**
   * @brief Constructs a new CircleContainer object
   * @param _name Name of the container (default "container")
   */
  CircleContainer(std::string _name = "container",
                  std::vector<Circle> _container = {});

  /// @name Setters
  /// @{
  void setName(std::string n);              ///< Sets the name of the container
  void setContainer(std::vector<Circle> c); ///< Sets the container
  /// @}

  /// @name Getters
  /// @{
  std::string getName() const; ///< Returns name of the container
  const std::vector<Circle> &getContainer() const; ///< Returns the container
  std::vector<Circle> &getContainer();
  /// @}

  /// @name Methods
  /// @{
  /**
   * @brief Adds a Circle to the container
   * @param c Circle to add
   */
  std::string addCircle(const Circle &c);

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
  std::string circlesToShape(sf::RenderWindow &w);
};

#endif // CIRCLECONTAINER_H
