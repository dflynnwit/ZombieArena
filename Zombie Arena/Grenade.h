//
// Created by Pokora on 02/01/2020.
//

#ifndef ZOMBIEARENA_GRENADE_H
#define ZOMBIEARENA_GRENADE_H


#include "Entity.h"
#include "Zombie.h"

class Grenade : public Entity{
private:
    const float FUSE_TIME = 2;
    bool m_InFlight = true;
    int m_grenadeSpeed = 100;
    float m_grenadeDistanceX;
    float m_grenadeDistanceY;

    float m_MinX;
    float m_MaxX;
    float m_MinY;
    float m_MaxY;

    float m_armedTime;

public:
    void Throw(int startX, int startY, int targetX, int targetY);

    bool Update(float timePassed);

    int Explode(std::vector<Entity*>& walls, std::vector<Zombie*>& zombies, int explosionRadius = 100, int explosionDamage = 5);
};


#endif //ZOMBIEARENA_GRENADE_H
