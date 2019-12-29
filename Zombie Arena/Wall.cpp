//
// Created by Pokora on 28/12/2019.
//

#include "Wall.h"

void Wall::Spawn(float x, float y, bool isEdge) {
    m_Position.x = x * m_Sprite.getLocalBounds().width;
    m_Position.y = y * m_Sprite.getLocalBounds().height;

    m_Rotation = 0;

    if(isEdge)
        m_Sprite.setColor(sf::Color::Red);

    Update();
}

Wall::Wall() : Entity("../Resources/graphics/wall.png"){
    srand(m_Position.x * m_Position.y);
    int r = rand() % 2;
    if(r == 0)
        SetSprite("../Resources/graphics/wall/1.png");
    else
        SetSprite("../Resources/graphics/wall/5.png");
}
