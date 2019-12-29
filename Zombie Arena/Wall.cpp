//
// Created by Pokora on 28/12/2019.
//

#include "Wall.h"

void Wall::Spawn(float x, float y) {
    m_Position.x = x * m_Sprite.getLocalBounds().width;
    m_Position.y = y * m_Sprite.getLocalBounds().height;

    m_Rotation = 0;
    Update();
}

Wall::Wall() : Entity("../Resources/graphics/wall.png"){

}
