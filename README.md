# Video-Game-Engine
This repository contains my ongoing work on a custom video game engine written in C++ using SFML and ImGui.

The project has recently been refactored to improve modularity, maintainability, and ease of extension.

## Engine Architecture
The core architecture of the engine is based on a Scene Manager responsible for:

- Tracking which scene is currently active
- Forwarding window and input events to the active scene
- Managing scene transitions through a lightweight command system

Each scene can emit a SceneCommand (e.g. GoToGame, Exit), which is processed by the engine loop to trigger scene changes or application shutdown.

## UI System
To simplify UI creation inside scenes, the engine provides reusable UI components:

- **Button**:
Handles mouse interaction, hover state, and click callbacks.

- **Title**: 
A simple drawable element for displaying title sprites.

These components allow UI logic to remain encapsulated within each scene without coupling it to the engine core.

## Current Features
Current Features:
- Main window with a Title Scene
- Interactive Start and Close buttons
- Scene switching via command-based flow
- Clean separation between:
  - Engine core
  - Scene logic
  - UI elements

## Behavior
- Pressing Start transitions to an empty game scene
- Pressing Close exits the application

## Screenshots
The Main Window of the engine is shows like this:
<img width="1562" height="1239" alt="image" src="https://github.com/user-attachments/assets/07d13bd7-c6c5-4396-9797-973c0acb5891" />

## Compile instructions
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
./bin/Game
```

## Notes
- The engine uses RAII-based resource management
- ImGui-SFML is initialized and shut down exclusively by the engine (not by scenes)
- Scenes are responsible only for their own logic and resources
