/**
 * @file circle.h
 * @author Jaime
 * @brief Circle class declaration
 * @version 0.1
 * @date 23/10/25
 * @copyright Copyright (c) 2023
 *
 * @defgroup CircleModule Circle Class
 * @brief Circle class with physical and rendering properties
 * @{
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <vector>

/**
 * @class Circle
 * @brief Represents a circle with position, velocity, mass, radius, and color.
 *
 * The Circle class allows defining a circle that can be rendered or not,
 * with basic physical properties and RGB color components.
 */
class Circle {
private:
  std::string name;           ///< Name of the circle
  bool render;                ///< Indicates whether it should be rendered
  float radius;               ///< Radius of the circle
  float mass;                 ///< Mass of the circle
  float xPos, yPos;           ///< Position in 2D coordinates
  float xVel, yVel;           ///< Velocity in 2D coordinates
  int rColor, gColor, bColor; ///< RGB color components

public:
  /**
   * @brief Constructs a new Circle object with specified properties
   * @param _name Name of the circle (default "circle")
   * @param _render True if it should be rendered (default true)
   * @param _radius Radius of the circle (default 1.0)
   * @param _mass Mass of the circle (default 1.0)
   * @param _xPos Initial X position (default 0.0)
   * @param _yPos Initial Y position (default 0.0)
   * @param _xVel Initial X velocity (default 1.0)
   * @param _yVel Initial Y velocity (default 1.0)
   * @param _rColor Red component (0-255, default 255)
   * @param _gColor Green component (0-255, default 255)
   * @param _bColor Blue component (0-255, default 255)
   */
  Circle(std::string _name = "circle", bool _render = true,
         float _radius = 1.0f, float _mass = 1.0f, float _xPos = 0.f,
         float _yPos = 0.f, float _xVel = 1.0f, float _yVel = 1.0f,
         int _rColor = 255, int _gColor = 255, int _bColor = 255);

  /// @name Setters
  /// @{
  void setName(std::string n); ///< Sets the circle's name
  void setRender(bool r);      ///< Enables or disables rendering
  void setRadius(float r);     ///< Sets the radius
  void setMass(float m);       ///< Sets the mass
  void setXPos(float p);       ///< Sets the X position
  void setYPos(float p);       ///< Sets the Y position
  void setXVel(float v);       ///< Sets the X velocity
  void setYVel(float v);       ///< Sets the Y velocity
  void setRColor(int r);       ///< Sets the red component
  void setGColor(int g);       ///< Sets the green component
  void setBColor(int b);       ///< Sets the blue component
  /// @}

  /// @name Getters
  /// @{
  std::string getName() const; ///< Returns the name
  bool getRender() const;      ///< Returns true if rendered
  float getRadius() const;     ///< Returns the radius
  float getMass() const;       ///< Returns the mass
  float getXPos() const;       ///< Returns the X position
  float getYPos() const;       ///< Returns the Y position
  float getXVel() const;       ///< Returns the X velocity
  float getYVel() const;       ///< Returns the Y velocity
  int getRColor() const;       ///< Returns the red component
  int getGColor() const;       ///< Returns the green component
  int getBColor() const;       ///< Returns the blue component
                               /// @}
};

#endif // CIRCLE_H

/** @} */ // end of CircleModule
