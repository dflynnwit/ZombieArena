//
// Created by Pokora on 28/12/2019.
//

#include "Wall.h"

void Wall::Spawn(float x, float y, bool isEdge, int r) {
    m_Position.x = x * m_Sprite.getLocalBounds().width;
    m_Position.y = y * m_Sprite.getLocalBounds().height;

    m_Rotation = r * 90;

    if(isEdge)
        m_Sprite.setColor(sf::Color::Red);

    Update();
}

Wall::Wall(float x, float y, bool isEdge) : Entity("../Resources/graphics/wall.png"){
    srand(x + y);
    int r = rand();
    std::cout << "x: " << x << ", y: " << y << ", s: " << x + y << ", r: " << r << std::endl;
    if(r%10 == 0)
        SetSprite("../Resources/graphics/wall/5.png");
    else
        SetSprite("../Resources/graphics/wall/1.png");

    Spawn(x, y, isEdge, 0);
}
