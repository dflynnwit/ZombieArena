//
// Created by Pokora on 02/01/2020.
//

#include "Key.h"

Key::Key(int x, int y){
    SetSprite("../Resources/graphics/keycard.png");

    m_Position.x = x;
    m_Position.y = y;

    m_Rotation = 0;

    m_collected = false;

    Update();
}

void Key::Collect() {
    m_collected = true;
}

bool Key::isCollected() {
    return m_collected;
}

void Key::Draw(RenderWindow& window) {
    if(!m_collected)
        Entity::Draw(window);
}
