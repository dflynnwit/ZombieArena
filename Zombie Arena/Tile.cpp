//
// Created by Pokora on 28/12/2019.
//

#include <random>
#include "Tile.h"

void Tile::Spawn(float x, float y, bool isEdge, int r) {
    m_Position.x = x * m_Sprite.getLocalBounds().width;
    m_Position.y = y * m_Sprite.getLocalBounds().height;

    m_Rotation = r * 90;

    if(isEdge)
        m_Sprite.setColor(sf::Color::Red);

    Update();
}

Tile::Tile(float x, float y, TYPE type, bool isEdge){
    int r = rand();

    if(type == Tile::TYPE::WALL) {
        if (r % 10 == 0)
            SetSprite("../Resources/graphics/wall/5.png");
        else
            SetSprite("../Resources/graphics/wall/1.png");

        Spawn(x, y, isEdge, 0);
    }
    else if(type == Tile::TYPE::FLOOR){
        switch(r % 5){
            case 0:
                SetSprite("../Resources/graphics/floor/ft_broken02_c.png");
                break;
            case 1:
                SetSprite("../Resources/graphics/floor/ft_conc01_c.png");
                break;
            default:
                SetSprite("../Resources/graphics/floor/ft_broken03_c.png");
                break;
        }

        Spawn(x, y, false, r % 4);
    }
}