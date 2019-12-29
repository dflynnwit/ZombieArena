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
    std::vector<Wall>* m_walls;
    float m_placementThreshold;
public:
    MazeGenerator(float placementThreshold = .5);

    void GenerateMazeData(int width, int height);
    std::vector<Wall>* CreateMaze();
    std::vector<std::vector<int>> GetData();

    void SetPlacementThreshold(float threshold);
    float GetPlacementThreshold();
};


#endif //ZOMBIEARENA_MAZEGENERATOR_H
