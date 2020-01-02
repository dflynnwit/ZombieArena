//
//  Player.cpp
//  Zombie Arena
//

//#include "stdafx.h" // <- Visual Studio only
#include "player.hpp"
#include "TextureHolder.h"

#include <iostream>

Player::Player() : Entity("../Resources/graphics/player.png")
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;

    // Associate a texture with the sprite
    // !!Watch this space!!
//    m_Sprite.setTexture(TextureHolder::GetTexture("../Resources/graphics/player.png"));

    // Set the origin of the sprite to the centre,
    // for smooth rotation
//    m_Sprite.setOrigin(25, 25);
}

void Player::spawn(int x, int y, Vector2f resolution) {
    // Place the player in the middle of the arena
    m_Position.x = x;
    m_Position.y = y;

    // Store the resolution for future use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
    return m_LastHit;
}

bool Player::hit(Time timeHit)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)// 2 tenths of second
    {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    else
    {
        return false;
    }

}

FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
    return m_Position;
}

float Player::getRotation()
{
    return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
    return m_Sprite;
}

int Player::getHealth()
{
    return m_Health;
}

void Player::setMoveRight(bool right) {
    m_RightPressed = right;
}

void Player::setMoveLeft(bool left) {
    m_LeftPressed = left;
}

void Player::setMoveDown(bool down) {
    m_DownPressed = down;
}

void Player::setMoveUp(bool up) {
    m_UpPressed = up;
}

void Player::update(float elapsedTime, Vector2i mousePosition, std::vector<Tile>& walls)
{
    Vector2f origPosition = m_Position;
    float origAngle = m_Sprite.getRotation();

    //Since true is 1 and false is 0 we can calculate displacement by subtracting opposite values multiplied by the booleans
    m_Position.x += (m_Speed * m_RightPressed - m_Speed * m_LeftPressed) * elapsedTime;
    m_Position.y += (m_Speed * m_DownPressed - m_Speed * m_UpPressed) * elapsedTime;

    // Calculate the angle the player is facing
    m_Rotation = (atan2(mousePosition.y - m_Resolution.y / 2,
                        mousePosition.x - m_Resolution.x / 2)
                  * 180) / 3.141;

    for(int i = 0; i < walls.size(); i++)
        if(Collision(walls[i])){
            //If destination would collide with wall, push player back by 1 pixel in a direction from that wall to the player
            float magnitude = Distance(walls[i]);
            m_Position.x += (origPosition.x - walls[i].GetPosition().x) / magnitude ;
            m_Position.y += (origPosition.y - walls[i].GetPosition().y) / magnitude ;
            break;
        }

    Update();
}

void Player::draw(RenderWindow &window) {
//    RectangleShape border(Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height));
//    border.setFillColor(Color(0, 0, 255, 200));
//    border.setOrigin(m_Sprite.getOrigin());
//    border.setPosition(m_Position);
//    border.setRotation(m_Sprite.getRotation());
//    window.draw(border);

    Draw(window);
}

void Player::upgradeSpeed()
{
    // 20% speed upgrade
    m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
    // 20% max health upgrade
    m_MaxHealth += (START_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount)
{
    m_Health += amount;

    // But not beyond the maximum
    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}