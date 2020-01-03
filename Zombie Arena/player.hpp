//
//  player.hpp
//  Zombie Arena
//

#ifndef player_hpp
#define player_hpp

#include <SFML/Graphics.hpp>
#include <cmath>       /* atan2 */
#include "Entity.h"
#include "Tile.h"


using namespace sf;

class Player : public Entity
{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;

    // What is the screen resolution
    Vector2f m_Resolution;

    // What size is the current arena
    IntRect m_Arena;

    // How big is each tile of the arena
    int m_TileSize;

    // Which directions is the player currently moving in
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

    // How much health has the player got?
    int m_Health;
    // What is the maximum health the player can have
    int m_MaxHealth;

    // When was the player last hit
    Time m_LastHit;

    // Speed in pixels per second
    float m_Speed;

    Sprite m_flashlightSprite;

public:

    Player();

    void spawn(int x, int y, Vector2f resolution);

    // Call this at the end of every game
    void resetPlayerStats();

    // Handle the player getting hit by a zombie
    bool hit(Time timeHit);

    // How long ago was the player last hit
    Time getLastHitTime();

    // Where is the player
    FloatRect getPosition();

    // Where is the center of the player?
    Vector2f getCenter();

    // Which angle is the player facing?
    float getRotation();

    // Send a copy of the sprite to main
    Sprite getSprite();

    // How much health has the player currently got?
    int getHealth();

    void setMoveUp(bool up);
    void setMoveDown(bool down);
    void setMoveLeft(bool left);
    void setMoveRight(bool right);

    void draw(RenderWindow &window);

    // We will call this function once every frame
    void update(float elapsedTime, Vector2i mousePosition, std::vector<Tile *> &walls);

    // Give player a speed boost
    void upgradeSpeed();

    // Give the player some health
    void upgradeHealth();

    // Increase the maximum amount of health the player can have
    void increaseHealthLevel(int amount);

    bool isHurt();
};

#endif /* player_hpp */
