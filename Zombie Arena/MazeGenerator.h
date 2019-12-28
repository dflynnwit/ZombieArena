//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_MAZEGENERATOR_H
#define ZOMBIEARENA_MAZEGENERATOR_H

#include <vector>
#include <ctime>
#include <cstdlib>
#include "Wall.h"

class MazeGenerator {
private:
    std::vector<std::vector<int>> m_mazeData;
    float m_placementThreshold;
    int m_nOfWalls;
public:
    MazeGenerator();
    MazeGenerator(float placementThreshold);

    void GenerateMazeData(int width, int height);
    Wall* CreateMaze();
    std::vector<std::vector<int>> GetData();
};


#endif //ZOMBIEARENA_MAZEGENERATOR_H
