//
// Created by Pokora on 02/01/2020.
//

#ifndef ZOMBIEARENA_GRENADE_H
#define ZOMBIEARENA_GRENADE_H


#include "Entity.h"
#include "Zombie.h"
#include "Tile.h"

class Grenade : public Entity{
private:
    const float FUSE_TIME = 2;
    float m_grenadeSpeed = 200;
    float m_grenadeDistanceX;
    float m_grenadeDistanceY;

    float m_MinX;
    float m_MaxX;
    float m_MinY;
    float m_MaxY;

    float m_armedTime;

public:
    Grenade();

    void Throw(int startX, int startY, int targetX, int targetY);

    bool Update(float timePassed);

    int Explode(std::vector<Tile*>& walls, std::vector<Zombie*>& zombies, int explosionRadius = 100, int explosionDamage = 5);
};


#endif //ZOMBIEARENA_GRENADE_H
