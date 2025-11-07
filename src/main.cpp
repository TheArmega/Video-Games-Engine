/**
 * @file main.cpp
 * @brief Entry point for the VideoGameEngine using SFML and ImGui-SFML
 * @author Jaime
 * @version 0.1
 * @date 23/10/25
 *
 * @details
 * This file initializes the SFML window and ImGui-SFML integration,
 * manages the Circle database, populates a CircleContainer, and runs
 * the main render loop displaying circles and ImGui widgets.
 */

#include "app.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Main function of the VideoGameEngine
 *
 * Initializes the window and ImGui-SFML, creates example Circle objects,
 * stores them in the database, populates the CircleContainer, and runs
 * the main render loop with ImGui GUI elements.
 *
 * @return int Returns 0 on success, -1 on failure (ImGui initialization
 * failure)
 */
int main() {

  // Run application
  App::run();
}
