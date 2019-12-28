//
// Created by Pokora on 26/11/2019.
//

#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

bool Zombie::hit() {
    if(--m_Health <= 0){
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture("../Resources/graphics/blood.png"));
    }

    //Return false if still alive
    return !m_Alive;
}

bool Zombie::isAlive() {
    return m_Alive;
}

void Zombie::spawn(float startX, float startY, int type, int seed) {
    switch (type){
        case 0:
            //Bloater
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/bloater.png"));
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            break;
        case 1:
            //Chaser
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/chaser.png"));
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            break;
        case 2:
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/crawler.png"));
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            break;
    }

    //Randomize speed to prevent bunching
    srand((int)time(0) * seed);
    float modifier = (rand() % MAX_VARIANCE) + OFFSET;
    modifier /= 100;
    m_Speed *= modifier;

    m_Position.x = startX;
    m_Position.y = startY;
}

FloatRect Zombie::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite() {
    return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation) {
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    // Update the zombie position variables
    if (playerX > m_Position.x)
    {
        m_Position.x = m_Position.x + m_Speed * elapsedTime;
    }

    if (playerY > m_Position.y)
    {
        m_Position.y = m_Position.y + m_Speed * elapsedTime;
    }

    if (playerX < m_Position.x)
    {
        m_Position.x = m_Position.x - m_Speed * elapsedTime;
    }

    if (playerY < m_Position.y)
    {
        m_Position.y = m_Position.y - m_Speed * elapsedTime;
    }

    // Face the sprite in the correct direction
    m_Rotation = (atan2(playerY - m_Position.y,
                         playerX - m_Position.x)
                   * 180) / 3.141;

    Update();
}

void Zombie::draw(RenderWindow &window) {
    RectangleShape border(Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height));
    border.setFillColor(Color(255, 0, 0, 200));
    border.setOrigin(m_Sprite.getOrigin());
    border.setPosition(m_Position);
    border.setRotation(m_Sprite.getRotation());
    window.draw(border);

    Draw(window);
}

Zombie::Zombie() {

}
