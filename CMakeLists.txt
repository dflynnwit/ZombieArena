cmake_minimum_required(VERSION 3.15)
project(ZombieArena)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES "Zombie Arena/")

include_directories(Resources)
include_directories(Resources/code)
include_directories(Resources/graphics)
include_directories(Resources/sound)
#include_directories(C:/Dev/SFML-2.5.1_for_MinGW-7.3.0/include)

add_executable(ZombieArena ${SOURCE_FILES}/ZombieArena.cpp
        ${SOURCE_FILES}/player.cpp  ${SOURCE_FILES}/Arena.cpp "Zombie Arena/TextureHolder.cpp" "Zombie Arena/TextureHolder.h" "Zombie Arena/Zombie.cpp" "Zombie Arena/Zombie.h" "Zombie Arena/ZombieHorde.cpp" "Zombie Arena/ZombieHorde.h" "Zombie Arena/Bullet.cpp" "Zombie Arena/Bullet.h" "Zombie Arena/Pickup.cpp" "Zombie Arena/Pickup.h" "Zombie Arena/Entity.h" "Zombie Arena/Entity.cpp" "Zombie Arena/Wall.cpp" "Zombie Arena/Wall.h" "Zombie Arena/MazeGenerator.cpp" "Zombie Arena/MazeGenerator.h")

# Detect and add SFML
set(SFML_DIR C:/Dev/SFML-2.5.1_for_MinGW-7.3.0/lib/cmake/SFML)
find_package(SFML REQUIRED COMPONENTS system window graphics audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(ZombieArena sfml-system sfml-window sfml-graphics sfml-audio)
endif()