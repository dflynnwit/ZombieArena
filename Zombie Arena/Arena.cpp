//
// Created by Pokora on 26/11/2019.
//

#include "Arena.h"

int createBackground(VertexArray &rVA, IntRect arena) {
    //Set up tile/texture size
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

    rVA.setPrimitiveType(Quads);

    //Set size of vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    //Start at beginning of va
    int currrentVertex = 0;

    srand((int)time(0));

    for(int w = 0; w < worldWidth; w++){
        for(int h = 0; h < worldHeight; h++){
            //Position each vertex in current quad
            rVA[currrentVertex].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currrentVertex + 1].position = Vector2f(w * TILE_SIZE + TILE_SIZE, h * TILE_SIZE);
            rVA[currrentVertex + 2].position = Vector2f(w * TILE_SIZE + TILE_SIZE, h * TILE_SIZE + TILE_SIZE);
            rVA[currrentVertex + 3].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE + TILE_SIZE);

            if(h == 0 || h == worldHeight -1 || w == 0 || w == worldWidth -1){
                //Use wall texture on edges
                rVA[currrentVertex].texCoords = Vector2f(0, TILE_TYPES * TILE_SIZE);
                rVA[currrentVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);
                rVA[currrentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE + TILE_SIZE);
                rVA[currrentVertex + 3].texCoords = Vector2f(0, TILE_TYPES * TILE_SIZE + TILE_SIZE);
            }
            else
            {
                //use random floor texture
                int rng = (rand() % TILE_TYPES);
                int verticalOffset = rng * ( TILE_SIZE);

                rVA[currrentVertex].texCoords = Vector2f(0, verticalOffset);
                rVA[currrentVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
                rVA[currrentVertex + 2].texCoords = Vector2f(TILE_SIZE, verticalOffset + TILE_SIZE);
                rVA[currrentVertex + 3].texCoords = Vector2f(0, verticalOffset + TILE_SIZE);
            }

            currrentVertex += VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}
