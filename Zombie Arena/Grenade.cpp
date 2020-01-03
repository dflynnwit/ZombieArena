//
// Created by Pokora on 02/01/2020.
//

#include "Grenade.h"

void Grenade::Throw(int startX, int startY, int targetX, int targetY) {
    //Keep track of bullet
    m_armedTime = FUSE_TIME;
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    //Calculate gradient
    float gradient = (startX - targetX)/(startY-targetY);

    //Gradient must be positive
    if(gradient < 0)
        gradient *= -1;

    float ratioXY = m_grenadeSpeed/(1+gradient);

    //Set horizontal and vertical speeds
    m_grenadeDistanceY = ratioXY;
    m_grenadeDistanceX = ratioXY * gradient;

    //Point bullet in right direction
    if(targetX < startX)
        m_grenadeDistanceX *= -1;
    if(targetY < startY)
        m_grenadeDistanceY *= -1;

    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;
}

bool Grenade::Update(float timePassed) {
    if(m_InFlight) {
        m_armedTime -= timePassed;
        if (m_armedTime < 0) {
            m_InFlight = false;
            return true;
        } else {
            //Update position
            m_Position.x += m_grenadeDistanceX * timePassed;
            m_Position.y += m_grenadeDistanceY * timePassed;

            return false;
        }
    }
}

int Grenade::Explode(std::vector<Entity *> &walls, std::vector<Zombie *> &zombies, int explosionRadius, int explosionDamage) {
    int points = 0;

    for(auto wall : walls) {
        if (Distance(*wall) < explosionRadius)
            wall->SetActive(false);
    }
    for(auto zombie : zombies){
        if(Distance(*zombie) < explosionRadius){
            if(zombie->hit(explosionDamage))
                points += 10;
        }
    }

    return points;
}
