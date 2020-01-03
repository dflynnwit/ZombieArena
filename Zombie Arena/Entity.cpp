//
// Created by Pokora on 28/12/2019.
//

#include <cmath>
#include "Entity.h"

Entity::Entity(const std::string filename) {
    m_active = 1;
    SetSprite(filename);
}

Entity::Entity(const std::string filename, int x, int y) {
    m_active = 1;
    m_Position.x = x;
    m_Position.y = y;
    m_Rotation = 0;

    SetSprite(filename);
}

void Entity::Draw(RenderWindow &window){
    if(m_active)
        window.draw(m_Sprite);
}

bool Entity::Collision(Entity& entity)
{
    return m_active && entity.isActive() && m_Sprite.getGlobalBounds().intersects(entity.m_Sprite.getGlobalBounds());
}

void Entity::SetActive(bool active)
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
    m_active = true;
}

void Entity::SetSprite(const std::string filename) {
    m_Sprite = Sprite(TextureHolder::GetTexture(filename));
    m_Sprite.setOrigin(m_Sprite.getLocalBounds().width/2, m_Sprite.getLocalBounds().height/2);

    Update();
}

void Entity::SetPosition(Vector2f position, float angle) {
    m_Sprite.setPosition(position.x, position.y);
    m_Sprite.setRotation(angle);
}

void Entity::Update() {
    m_Sprite.setPosition(m_Position.x, m_Position.y);
    m_Sprite.setRotation(m_Rotation);
}

float Entity::Distance(Entity &entity) {
    return sqrt(pow((m_Position.y - entity.m_Position.y), 2) + pow((m_Position.x - entity.m_Position.x), 2));
}

Vector2f Entity::GetPosition() {
    return m_Position;
}

bool Entity::isActive() {
    return m_active;
}
