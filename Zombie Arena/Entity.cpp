//
// Created by Pokora on 28/12/2019.
//

#include <cmath>
#include "Entity.h"

Entity::Entity(const std::string filename) {
    m_Sprite = GetComponent<SpriteComponent>();
    m_Transform = GetComponent<TransformComponent>();
    m_active = 1;
    SetSprite(filename);
}

Entity::Entity(const std::string filename, int x, int y) {
    m_Sprite = GetComponent<SpriteComponent>();
    m_Transform = GetComponent<TransformComponent>();
    m_active = 1;
    m_Transform->SetPosition(sf::Vector2f(x, y), 0);

    SetSprite(filename);
}

void Entity::Draw(RenderWindow &window){
    if(m_active)
        m_Sprite->Draw(window);
}

bool Entity::Collision(Entity& entity)
{
    sf::FloatRect ownBounds = m_Sprite->GetSprite().getGlobalBounds();
    sf::FloatRect colliderBounds = entity.GetSprite().getGlobalBounds();
    return m_active && entity.isActive() && ownBounds.intersects(colliderBounds);
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
    return m_Sprite->GetSprite();
}

Entity::Entity() {
    m_active = true;
}

void Entity::SetSprite(const std::string filename) {
    m_Sprite->SetSprite(TextureHolder::GetTexture(filename));

    Update();
}

void Entity::SetPosition(Vector2f position, float angle) {
    m_Transform->SetPosition(position, angle);
}

void Entity::Update() {
    m_Sprite->setPosition(GetPosition(), m_Transform->GetRotation());
}

float Entity::Distance(Entity &entity) {
    Vector2f ownPos = GetPosition();
    Vector2f entityPos = entity.GetPosition();
    return sqrt(pow((ownPos.y - entityPos.y), 2) + pow((ownPos.x - entityPos.x), 2));
}

Vector2f Entity::GetPosition() {
    return m_Transform->GetPosition();
}

float Entity::GetRotation() {
    return m_Transform->GetRotation();
}

bool Entity::isActive() {
    return m_active;
}