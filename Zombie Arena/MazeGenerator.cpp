//
// Created by Pokora on 28/12/2019.
//

#include <iostream>
#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(float placementThreshold) {
    m_placementThreshold = placementThreshold;
}

void MazeGenerator::GenerateMazeData(int width, int height, int enemyAmount, int keysAmount, float pickupChance) {
    //Initialize all values in size
    m_mazeData.clear();
    m_mazeData.resize(height+1, std::vector<int>(width+1, 0));
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
                }
            }
        }
    }

    addEntrance();
    addExit();
    addPickups(pickupChance);

    for(int i = 0; i < keysAmount; i++)
        addKeys();

    for(int i = 0; i < enemyAmount; i++)
        addEnemy();
}

std::vector<std::vector<int>> MazeGenerator::GetData() {
    return m_mazeData;
}

std::vector<Tile*> *MazeGenerator::CreateMaze() {
    m_walls = new std::vector<Tile*>();
    m_floor = new std::vector<Tile*>();

    for(int row = 0; row < m_mazeData.size(); row++){
        for(int col = 0; col < m_mazeData[0].size(); col++){
            if(m_mazeData[row][col] == 1) {
                m_walls->push_back(new Tile(col, row, Tile::TYPE::WALL));
                m_floor->push_back(new Tile(col, row, Tile::TYPE::FLOOR));
            }
            else if(m_mazeData[row][col] == 10) {
                m_walls->push_back(new Tile(col, row, Tile::TYPE::WALL, true));
            } else{
                m_floor->push_back(new Tile(col, row, Tile::TYPE::FLOOR));
            }
        }
    }

    return m_walls;
}

std::vector<Tile*> *MazeGenerator::GetFloor() {
    return m_floor;
}

void MazeGenerator::addEntrance() {
    for(int i = 3; i < m_mazeData.size(); i++){
        for(int j = 3; j < m_mazeData[0].size(); j++){
            if(m_mazeData[i][j] == 0) {
                m_mazeData[i][j] = 5;
                return;
            }
        }
    }
}

void MazeGenerator::addPickups(float pickupChance) {
    for(int i = 0; i < m_mazeData.size(); i++){
        for(int j = 0; j < m_mazeData[0].size(); j++){
            float r = (float)rand()/RAND_MAX;
            if(m_mazeData[i][j] == 0 && r <= pickupChance) {
                //Randomly choose between health pickup (2) or ammo pickup (3)
                m_mazeData[i][j] = rand()%2 == 0? 2 : 3;
            }
        }
    }
}

void MazeGenerator::addExit() {
    for(int i = m_mazeData.size() / 3 * 2; i < m_mazeData.size(); i++){
        for(int j = m_mazeData[0].size() / 3 * 2 ; j < m_mazeData[0].size() ; j++){
            if(m_mazeData[i][j] == 0) {
                m_mazeData[i][j] = 6;
                return;
            }
        }
    }
}

void MazeGenerator::addEnemy() {
    for(int i = rand() % m_mazeData.size(); i < m_mazeData.size(); i++){
        for(int j = rand() % m_mazeData[0].size(); j < m_mazeData[0].size(); j++)
            if(m_mazeData[i][j] != 1 && m_mazeData[i][j] != 10 && m_mazeData[i][j] != 5) {
                m_mazeData[i][j] = 4;
                return;
            }
    }
}

void MazeGenerator::addKeys() {
    bool keyPlaced = false;

    while(!keyPlaced) {
        for (int i = rand() % m_mazeData.size(); i < m_mazeData.size(); i++) {
            for (int j = rand() % m_mazeData[0].size(); j < m_mazeData[0].size(); j++) {
                if (m_mazeData[i][j] == 0) {
                    m_mazeData[i][j] = 7;
                    keyPlaced = true;
                    return;
                }
            }
        }
    }
}
