cmake_minimum_required(VERSION 3.15)
project(ZombieArena)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES "Zombie Arena/")

include_directories(Resources)
include_directories(Resources/code)
include_directories(Resources/graphics)
include_directories(Resources/sound)
include_directories("Zombie Arena")

set(SFML_DIR C:/Dev/SFML-2.5.1_for_MinGW-7.3.0/lib/cmake/SFML)
find_package(SFML COMPONENTS main audio system window graphics REQUIRED)
include_directories(C:/Dev/SFML-2.5.1_for_MinGW-7.3.0/include)

add_executable(ZombieArena ${SOURCE_FILES}/main.cpp
        ${SOURCE_FILES}/player.cpp)

#add_executable(ZombieArena
#    Resources/code/Player.cpp
#    Resources/code/Player.h
#    Resources/code/ZombieArena.cpp
#    Resources/graphics/ammo_icon.png
#    Resources/graphics/ammo_pickup.png
#    "Resources/graphics/background 1280-720.png"
#    Resources/graphics/background.png
#    Resources/graphics/background_sheet.png
#    Resources/graphics/bloater.png
#    Resources/graphics/blood.png
#    Resources/graphics/chaser.png
#    Resources/graphics/crawler.png
#    Resources/graphics/crosshair.png
#    Resources/graphics/health_pickup.png
#    Resources/graphics/player.png
#    Resources/graphics/sample.png
#    Resources/sound/hit.wav
#    Resources/sound/pickup.wav
#    Resources/sound/powerup.wav
#    Resources/sound/reload.wav
#    Resources/sound/reload_failed.wav
#    Resources/sound/shoot.wav
#    Resources/sound/splat.wav
#    "Zombie Arena/main.cpp"
#    "Zombie Arena/player.cpp"
#    "Zombie Arena/player.hpp")
