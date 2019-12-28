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

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize) {
    // Place the player in the middle of the arena
    m_Position.x = arena.width / 2;
    m_Position.y = arena.height / 2;
    // Copy the details of the arena to the player's m_Arena
    m_Arena.left = arena.left;
    m_Arena.width = arena.width;
    m_Arena.top = arena.top;
    m_Arena.height = arena.height;

    // Remember how big the tiles are in this arena
    m_TileSize = tileSize;

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

void Player::update(float elapsedTime, Vector2i mousePosition)
{
    //Since true is 1 and false is 0 we can calculate displacement by subtracting opposite values multiplied by the booleans
    m_Position.x += (m_Speed * m_RightPressed - m_Speed * m_LeftPressed) * elapsedTime;
    m_Position.y += (m_Speed * m_DownPressed - m_Speed * m_UpPressed) * elapsedTime;

    //TODO: Check for collisions before updating position instead

//    m_Sprite.setPosition(m_Position);

    // Keep the player in the arena
    if (m_Position.x > m_Arena.width - m_TileSize)
    {
        m_Position.x = m_Arena.width - m_TileSize;
    }

    if (m_Position.x < m_Arena.left + m_TileSize)
    {
        m_Position.x = m_Arena.left + m_TileSize;
    }

    if (m_Position.y > m_Arena.height - m_TileSize)
    {
        m_Position.y = m_Arena.height - m_TileSize;
    }

    if (m_Position.y < m_Arena.top + m_TileSize)
    {
        m_Position.y = m_Arena.top + m_TileSize;
    }

    // Calculate the angle the player is facing
    float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
                         mousePosition.x - m_Resolution.x / 2)
                   * 180) / 3.141;

//    m_Sprite.setRotation(angle);

    SetPosition(m_Position, angle);

}

void Player::draw(RenderWindow &window) {
    RectangleShape border(Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height));
    border.setFillColor(Color(0, 0, 255, 200));
    border.setOrigin(m_Sprite.getOrigin());
    border.setPosition(m_Position);
    border.setRotation(m_Sprite.getRotation());
    window.draw(border);

//    Draw(window);
    window.draw(m_Sprite);
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