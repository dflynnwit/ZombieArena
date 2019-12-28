//
// Created by Pokora on 28/12/2019.
//

#ifndef ZOMBIEARENA_MAZEGENERATOR_H
#define ZOMBIEARENA_MAZEGENERATOR_H

#include <vector>
#include <ctime>
#include <cstdlib>

class MazeGenerator {
private:
    std::vector<std::vector<int>> m_mazeData;
    float m_placementThreshold;
public:
    MazeGenerator();
    MazeGenerator(float placementThreshold);

    void GenerateMaze(int width, int height);
    std::vector<std::vector<int>> GetData();
};


#endif //ZOMBIEARENA_MAZEGENERATOR_H
