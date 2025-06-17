cmake_minimum_required(VERSION 3.21)
project(space-invaders)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(
	space-invaders ./src/main.cpp ./src/game_scene.cpp ./src/initial_menu.cpp
)

target_link_libraries(space-invaders PRIVATE Qt6::Widgets)
