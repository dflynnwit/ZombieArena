//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_WALL_H
#define ZOMBIEARENA_WALL_H


#include "Entity.h"

class Wall : public Entity{
private:

public:
    Wall(float x, float y, bool isEdge = false);
    void Spawn(float x, float y, bool isEdge, int r);
};


#endif //ZOMBIEARENA_WALL_H
