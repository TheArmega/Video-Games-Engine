#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class Engine {

private:
  std::string name = "Rabu";

public:
  // Constructor
  Engine(std::string _name);

  // Setters
  void setName(std::string n);

  // Getters
  std::string getName();

  void run();
};

#endif // ENGINE_H
