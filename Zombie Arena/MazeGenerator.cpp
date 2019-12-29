//
// Created by Pokora on 28/12/2019.
//

#include <iostream>
#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(float placementThreshold) {
    m_placementThreshold = placementThreshold;
}

void MazeGenerator::GenerateMazeData(int width, int height) {
    //Initialize all values in size
    m_mazeData.resize(height+1, std::vector<int>(width+1, 0));
    m_nOfWalls = 0;
    srand((int)time(0));

    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (i == 0 || j == 0 || i == height || j == width)
            {
                m_mazeData[i][j] = 10;
            }

            else if (i % 2 == 0 && j % 2 == 0)
            {
                float r = (float)rand() / (RAND_MAX);
                if (r > m_placementThreshold)
                {
                    m_mazeData[i][j] = 1;

                    int a = r < .5 ? 0 : (r < .5 ? -1 : 1);
                    int b = a != 0 ? 0 : (r < .5 ? -1 : 1);
                    m_mazeData[i+a][j+b] = 1;

                    m_nOfWalls += 2;
                }
            }
        }
    }
}

std::vector<std::vector<int>> MazeGenerator::GetData() {
    return m_mazeData;
}

Wall *MazeGenerator::CreateMaze() {
    Wall* walls = new Wall[m_nOfWalls];
    int index = 0;

    m_walls = new std::vector<Wall>();

    for(int row = 0; row < m_mazeData.size(); row++){
        for(int col = 0; col < m_mazeData[0].size(); col++){
            if(m_mazeData[row][col] == 1)
                walls[index++].Spawn(col,row);
            if(m_mazeData[row][col] == 10)
                walls[index++].Spawn(col,row, true);
        }
    }

    return walls;
}

int MazeGenerator::GetNofWalls() {
    return m_nOfWalls;
}
