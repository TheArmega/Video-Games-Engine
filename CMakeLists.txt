cmake_minimum_required(VERSION 3.15)
project(VideoGamesEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(VideoGamesEngine
  src/main.cpp
)

target_include_directories(VideoGamesEngine PUBLIC include)
