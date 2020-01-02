//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_MAZEGENERATOR_H
#define ZOMBIEARENA_MAZEGENERATOR_H

#include <vector>
#include <ctime>
#include <cstdlib>
#include "Tile.h"

class MazeGenerator {
private:
    std::vector<std::vector<int>> m_mazeData;
    std::vector<Tile>* m_walls;
    std::vector<Tile>* m_floor;
    float m_placementThreshold;

    void addEntrance();
    void addExit();
    void addPickups(float pickupChance);
    void addEnemy();
    void addKeys();
public:
    MazeGenerator(float placementThreshold = .1);

    void GenerateMazeData(int width, int height, int enemyAmount, int keysAmount, float pickupChance);
    std::vector<Tile>* CreateMaze();

    std::vector<std::vector<int>> GetData();

    void SetPlacementThreshold(float threshold);
    float GetPlacementThreshold();

    std::vector<Tile> *GetFloor();
};


#endif //ZOMBIEARENA_MAZEGENERATOR_H
