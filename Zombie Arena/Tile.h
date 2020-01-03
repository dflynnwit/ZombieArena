//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_TILE_H
#define ZOMBIEARENA_TILE_H


#include "Entity.h"

class Tile : public Entity{
private:
    bool m_edge;
public:
    enum class TileType{FLOOR, WALL};
    Tile(float x, float y, TileType = Tile::TileType::FLOOR, bool isEdge = false);
    void Spawn(float x, float y, bool isEdge, int r);
    bool isEdge();
};

#endif //ZOMBIEARENA_TILE_H
