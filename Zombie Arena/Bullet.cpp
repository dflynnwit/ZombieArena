//
//  bullet.cpp
//  Zombie Arena
//
//

//#include "stdafx.h" <- Visual Studio only
#include <iostream>
#include "Bullet.h"

// The constructor
Bullet::Bullet() : Entity()
{
    m_BulletShape.setSize(Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY,
                   float targetX, float targetY)
{
    //Keep track of bullet
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    //Calculate gradient
    float gradient = (startX - targetX)/(startY-targetY);

    //Gradient must be positive
    if(gradient < 0)
        gradient *= -1;

    float ratioXY = m_BulletSpeed/(1+gradient);

    //Set horizontal and vertical speeds
    m_BulletDistanceY = ratioXY;
    m_BulletDistanceX = ratioXY * gradient;

    //Point bullet in right direction
    if(targetX < startX)
        m_BulletDistanceX *= -1;
    if(targetY < startY)
        m_BulletDistanceY *= -1;

    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;

    //Position bullet at start
    m_BulletShape.setPosition(m_Position);

}

void Bullet::stop()
{
    m_InFlight = false;
}

bool Bullet::isInFlight()
{
    return m_InFlight;
}

FloatRect Bullet::getPosition()
{
    return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
    return m_BulletShape;
}


void Bullet::update(float elapsedTime)
{
    //Update position
    m_Position.x += m_BulletDistanceX * elapsedTime;
    m_Position.y += m_BulletDistanceY * elapsedTime;

    m_BulletShape.setPosition(m_Position);

    //Test out of range
    if(m_Position.x < m_MinX || m_Position.x > m_MaxX ||
    m_Position.y < m_MinY || m_Position.y > m_MaxY)
        m_InFlight = false;
}

void Bullet::draw(RenderWindow &window) {
    if(m_InFlight)
        window.draw(m_BulletShape);
}

bool Bullet::Collision(Entity &entity) {
    return m_active && entity.isActive() && m_BulletShape.getGlobalBounds().intersects(entity.GetSprite().getGlobalBounds());
}
