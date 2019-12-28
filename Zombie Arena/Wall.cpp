//
// Created by Pokora on 28/12/2019.
//

#include "Wall.h"

void Wall::Spawn(float x, float y) {
    m_Position.x = x;
    m_Position.y = y;

    m_Rotation = 0;
}

Wall::Wall() {

}
