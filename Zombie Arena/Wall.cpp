//
// Created by Pokora on 28/12/2019.
//

#include "Wall.h"

void Wall::Spawn(float x, float y) {
    m_Position.x = x * m_Sprite.getLocalBounds().width;
    m_Position.y = y * m_Sprite.getLocalBounds().height;

    m_Rotation = 0;

//    std::cout << m_Position.x << ":" << m_Position.y << "----" << m_Sprite.getPosition().x << ":" << m_Sprite.getPosition().y << "------";
    Update(); //TODO: CHECK POSITIONS BEFORE AND AFTER ! WHY IS IT 0 ?!
//    std::cout << m_Sprite.getPosition().x << ":" << m_Sprite.getPosition().y << std::endl;
}

Wall::Wall() : Entity("../Resources/graphics/wall.png"){

}
