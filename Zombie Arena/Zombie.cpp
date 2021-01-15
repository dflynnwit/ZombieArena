//
// Created by Pokora on 26/11/2019.
//

#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

bool Zombie::hit(int damage) {
    m_Health -= damage;
    if(m_Health <= 0){
        m_Alive = false;
//        m_Sprite.setTexture(TextureHolder::GetTexture("../Resources/graphics/blood.png"));
        Entity::SetSprite("../Resources/graphics/blood.png");
    }

    //Return false if still alive
    return !m_Alive;
}

bool Zombie::isAlive() {
    return m_Alive;
}

Zombie::Zombie(int x, int y) {
    int r = rand();
    switch (r % 3){
        case 0:
            //Bloater
//            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/bloater.png"));
            Entity::SetSprite("../Resources/graphics/bloater.png");
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            m_Damage = BLOATER_DAMAGE;
            m_Type = 0;
            break;
        case 1:
            //Chaser
//            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/chaser.png"));
            Entity::SetSprite("../Resources/graphics/chaser.png");
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            m_Damage = CHASER_DAMAGE;
            m_Type = 1;
            break;
        case 2:
//            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/crawler.png"));
            Entity::SetSprite("../Resources/graphics/crawler.png");
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            m_Damage = CRAWLER_DAMAGE;
            m_Type = 2;
            break;
    }

    //Randomize speed to prevent bunching
    float modifier = (r % MAX_VARIANCE) + OFFSET;
    modifier /= 100;
    m_Speed *= modifier;

    SetPosition(Vector2f(x, y), 0);
//    m_Position.x = x;
//    m_Position.y = y;
}


FloatRect Zombie::getPosition() {
    return m_Sprite->GetSprite().getGlobalBounds();
}

Sprite Zombie::getSprite() {
    return m_Sprite->GetSprite();
}

void Zombie::update(float elapsedTime, Entity &player, std::vector<Tile*>& walls) {
    float playerX = player.GetPosition().x;
    float playerY = player.GetPosition().y;

    float distanceToPlayer = Distance(player);
    if(distanceToPlayer < 200)
        m_Alerted = true;
    if(distanceToPlayer > 400)
        m_Alerted = false;

    if(m_Alerted) {
        Vector2f origPosition = m_Transform->GetPosition();
        float x = 0, y = 0;
        // Update the zombie position variables
        if (playerX > origPosition.x) {
            x = origPosition.x + m_Speed * elapsedTime;
        }

        if (playerY > origPosition.y) {
            y = origPosition.y + m_Speed * elapsedTime;
        }

        if (playerX < origPosition.x) {
            x = origPosition.x - m_Speed * elapsedTime;
        }

        if (playerY < origPosition.y) {
            y = origPosition.y - m_Speed * elapsedTime;
        }

        // Face the sprite in the correct direction
        float rotation = (atan2(playerY - origPosition.y,
                            playerX - origPosition.x)
                      * 180) / 3.141f;



        for (int i = 0; i < walls.size(); i++)
            if (Collision(*walls[i])) {
                //If destination would collide with wall, push player back by 1 pixel in a direction from that wall to the player
                float magnitude = Distance(*walls[i]);
                x = origPosition.x + (origPosition.x - walls[i]->GetPosition().x) / magnitude;
                y = origPosition.y + (origPosition.y - walls[i]->GetPosition().y) / magnitude;
                break;
            }

        Entity::SetPosition(Vector2f(x, y), rotation);
    }

    Update();
}

void Zombie::draw(RenderWindow &window) {
//    RectangleShape border(Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height));
//    border.setFillColor(Color(255, 0, 0, 200));
//    border.setOrigin(m_Sprite.getOrigin());
//    border.setPosition(m_Position);
//    border.setRotation(m_Sprite.getRotation());
//    window.draw(border);

    Draw(window);
}

std::pair<int, int> Zombie::OnDeath(Entity &player, std::vector<Tile *> &walls, std::vector<Zombie*>& zombies, int effectDistance) {
    std::pair<int, int> damageAndPoints;
    damageAndPoints.first = 0;
    damageAndPoints.second = 0;

    if(m_Type == 0){
        if(Distance(player) < effectDistance)
            damageAndPoints.first = 30;

        //Destroy nearby walls
        for(auto wall : walls){
            if(Distance(*wall) < effectDistance)
                wall->SetActive(false);
        }

        //Kill nearby zombies and award points
        for(auto zombie : zombies){
            if(Distance(*zombie) < effectDistance){
                if(zombie->hit(5))
                    damageAndPoints.second += 10;
            }
        }
    }

    return damageAndPoints;
}

int Zombie::GetDamage() {
    return m_Damage;
}

int Zombie::GetZombieType() {
    return m_Type;
}
