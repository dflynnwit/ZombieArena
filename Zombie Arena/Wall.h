//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_WALL_H
#define ZOMBIEARENA_WALL_H


#include "Entity.h"

class Wall : public Entity{
private:
    IntRect m_Arena;
public:
    Wall();

    void Spawn();
};


#endif //ZOMBIEARENA_WALL_H
