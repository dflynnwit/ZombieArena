//
// Created by Pokora on 24/12/2019.
//

#ifndef ZOMBIEARENA_ENTITY_H
#define ZOMBIEARENA_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"


class Entity
{
public:
    Entity();

    Entity(const std::string filename);

    Entity(const std::string filename, int x, int y);

    bool Collision(Entity& entity);

    float Distance(Entity& entity);

    void SetSprite(const std::string filename);

    void SetPosition(Vector2f position, float angle);

    void Update();

    void SetActive(int active);

    int GetActive();

    int GetGroup();

    Sprite GetSprite();

    Vector2f GetPosition();

    void Draw(RenderWindow &window);

    sf::Vector2f velocity;
protected:
    int m_active, m_group_id;
    Sprite m_Sprite;
    Vector2f m_Position;
    float m_Rotation;
};

#endif //ZOMBIEARENA_ENTITY_H
