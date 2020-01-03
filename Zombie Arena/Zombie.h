//
// Created by Pokora on 26/11/2019.
//

#ifndef ZOMBIEARENA_ZOMBIE_H
#define ZOMBIEARENA_ZOMBIE_H



#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Tile.h"

using namespace sf;

class Zombie : public Entity
{
private:
    // How fast is each zombie type?
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED = 80;
    const float CRAWLER_SPEED = 20;

    // How tough is each zombie type
    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;

    // How strong is each zombie type
    const float BLOATER_DAMAGE = 20;
    const float CHASER_DAMAGE = 15;
    const float CRAWLER_DAMAGE = 10;

    // Make each zombie vary its speed slightly
    const int MAX_VARIANCE = 30;
    const int OFFSET = 101 - MAX_VARIANCE;

    // How fast can this one run/crawl?
    float m_Speed;

    // How much health has it got?
    float m_Health;

    // Is it still alive?
    bool m_Alive=true;

    //Is the zombie aware of player
    bool m_Alerted = false;

    //Store type (how to store enum?)
    int m_Type;

    //Store how much damage it deals
    int m_Damage;

    // Public prototypes go here
public:
    Zombie();

    Zombie(int x, int y);

    // Handle when a bullet hits a zombie
    bool hit(int damage = 1);

    // Find out if the zombie is alive
    bool isAlive();

    // Spawn a new zombie
    void spawn(float startX, float startY, int type, int seed);

    // Return a rectangle that is the position in the world
    FloatRect getPosition();

    // Get a copy of the sprite to draw
    Sprite getSprite();

    int GetDamage();

    // Update the zombie each frame
    void update(float elapsedTime, Entity &player, std::vector<Tile*>& walls);

    void draw(RenderWindow& window);

    std::pair<int, int> OnDeath(Entity& player, std::vector<Tile*>& walls, std::vector<Zombie*>& zombies, int effectDistance = 100);

    int GetZombieType();
};


#endif //ZOMBIEARENA_ZOMBIE_H
