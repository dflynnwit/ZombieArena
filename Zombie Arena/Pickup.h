//
// Created by Pokora on 21/12/2019.
//

#ifndef ZOMBIEARENA_PICKUP_H
#define ZOMBIEARENA_PICKUP_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;

class Pickup : public Entity{
private:
    //Start value for health pickups
    const int HEALTH_START_VALUE = 50;
    const int AMMO_START_VALUE = 12;
    const int START_WAIT_TIME = 10;
    const int START_SECONDS_TO_LIVE = 5;

    // The arena it exists in
    IntRect m_Arena;

    // How much is this pickup worth?
    int m_Value;

    // What type of pickup is this?
    // 1 = health, 2 = ammo
    int m_Type;

    // Handle spawning and disappearing
    bool m_Spawned;
    float m_SecondsSinceSpawn;
    float m_SecondsSinceDeSpawn;
    float m_SecondsToLive;
    float m_SecondsToWait;


public:
    enum TYPE{HEALTH = 1, AMMO = 2};
    Pickup(TYPE type, Vector2f position);

    // Prepare a new pickup
    void setArena(IntRect arena);

    void spawn();

    // Check the position of a pickup
    FloatRect getPosition();

    // Get the sprite for drawing
    Sprite getSprite();

    // Let the pickup update itself each frame
    void update(float elapsedTime);

    // Is this pickup currently spawned?
    bool isSpawned();

    // Get the goodness from the pickup
    int gotIt();

    void draw(RenderWindow &window);

    // Upgrade the value of each pickup
    void upgrade();

};

#endif //ZOMBIEARENA_PICKUP_H
