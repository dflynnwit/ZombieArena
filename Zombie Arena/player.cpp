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
}

void Player::spawn(int x, int y, Vector2f resolution) {
    // Place the player in the middle of the arena
    SetPosition(Vector2f(x, y), 0);

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

bool Player::hit(Time timeHit, int damage)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)// 2 tenths of second
    {
        m_LastHit = timeHit;
        m_Health -= damage;
        return true;
    }
    else
    {
        return false;
    }

}

FloatRect Player::getPosition()
{
    return getSprite().getGlobalBounds();
}

Vector2f Player::getCenter()
{
    return Entity::GetPosition();
}

float Player::getRotation()
{
    return Entity::GetRotation();
}

Sprite Player::getSprite()
{
    return Entity::GetSprite();
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

void Player::update(float elapsedTime, Vector2i mousePosition, std::vector<Tile *> &walls)
{
    Vector2f origPosition = m_Transform->GetPosition();

    Vector2f newPos = Vector2f(
            origPosition.x + (m_Speed * m_RightPressed - m_Speed * m_LeftPressed) * elapsedTime,
            origPosition.y + (m_Speed * m_DownPressed - m_Speed * m_UpPressed) * elapsedTime);
    //Since true is 1 and false is 0 we can calculate displacement by subtracting opposite values multiplied by the booleans

    // Calculate the angle the player is facing
    float rotation = (atan2(mousePosition.y - m_Resolution.y / 2,
                        mousePosition.x - m_Resolution.x / 2)
                  * 180) / 3.141;

    Entity::SetPosition(newPos, rotation);

    for(int i = 0; i < walls.size(); i++)
        //TODO: This is obviously not working well
        if(Collision(*walls[i])){
            //If destination would collide with wall, push player back by 1 pixel in a direction from that wall to the player
            float magnitude = Distance(*walls[i]);

            Vector2f adjustedPos = Vector2f(
                    (origPosition.x - walls[i]->GetPosition().x) / magnitude,
                    (origPosition.y - walls[i]->GetPosition().y) / magnitude
                    );
            Entity::SetPosition(adjustedPos, rotation);
            break;
        }

    Update();
}

void Player::draw(RenderWindow &window) {
    Entity::Draw(window);
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

bool Player::isHurt() {
    return m_Health < m_MaxHealth;
}
