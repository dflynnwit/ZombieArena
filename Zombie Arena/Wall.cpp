//
// Created by Pokora on 28/12/2019.
//

#include "Wall.h"

void Wall::Spawn() {
    srand((int)time(0));
    m_Position.x = (rand() % m_Arena.width);
    m_Position.y = (rand() % m_Arena.height);

    m_Rotation = 0;
}
