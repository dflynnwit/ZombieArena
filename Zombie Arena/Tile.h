//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_TILE_H
#define ZOMBIEARENA_TILE_H


#include "Entity.h"

class Tile : public Entity{
private:
//    Tile::TYPE type;
public:
    enum class TYPE{FLOOR, WALL};
    Tile(float x, float y, TYPE = Tile::TYPE::FLOOR, bool isEdge = false);
    void Spawn(float x, float y, bool isEdge, int r);

};


#endif //ZOMBIEARENA_TILE_H
