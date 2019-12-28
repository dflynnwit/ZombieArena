//
// Created by Pokora on 28/12/2019.
//

#include "Entity.h"

Entity::Entity(const std::string filename) {
    m_active = 1;
    SetSprite(filename);
}

void Entity::Draw(RenderWindow &window){
    std::cout << "Drawing entity" << std::endl;
    window.draw(m_Sprite);
}

bool Entity::Collision(Entity& entity)
{
    return m_Sprite.getGlobalBounds().intersects(entity.m_Sprite.getGlobalBounds());
}

void Entity::SetActive(int active)
{
    m_active = active;
}

int Entity::GetActive() {
    return m_active;
}

int Entity::GetGroup() {
    return m_group_id;
}

Sprite Entity::GetSprite() {
    return m_Sprite;
}

Entity::Entity() {
    m_active = 1;
}

void Entity::SetSprite(const std::string filename) {
    m_Sprite = Sprite(TextureHolder::GetTexture(filename));
    m_Sprite.setOrigin(m_Sprite.getLocalBounds().width/2, m_Sprite.getLocalBounds().height/2);
//    m_Sprite.setOrigin(25, 25);
}

void Entity::SetPosition(Vector2f position, float angle) {
    m_Sprite.setPosition(position.x, position.y);
    m_Sprite.setRotation(angle);
}


