//
// Created by Pokora on 24/12/2019.
//

#ifndef ZOMBIEARENA_ENTITY_H
#define ZOMBIEARENA_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Object.h"


class Entity : public Object
{
public:
    Entity();

    Entity(const std::string &filename);

    Entity(const std::string &filename, int x, int y);

    bool Collision(Entity& entity);

    float Distance(Entity& entity);

    void SetSprite(const std::string filename);

    void SetPosition(Vector2f position, float angle);

    void Update();

    void SetActive(bool active);

    int GetActive();

    int GetGroup();

    Sprite GetSprite();

    Vector2f GetPosition();

    float GetRotation();

    void Draw(RenderWindow &window);

    sf::Vector2f velocity;

    bool isActive();
protected:
    int m_group_id;
    bool m_active;
    std::shared_ptr<SpriteComponent> m_Sprite;
    std::shared_ptr<TransformComponent> m_Transform;
};

#endif //ZOMBIEARENA_ENTITY_H
