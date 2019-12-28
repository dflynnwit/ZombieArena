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

    bool Collision(Entity& entity);

    void SetSprite(const std::string filename);

    void SetPosition(Vector2f position, float angle);

    void SetActive(int active);

    int GetActive();

    int GetGroup();

    Sprite GetSprite();

    void Draw(RenderWindow &window);

    sf::Vector2f velocity;
protected:
    int m_active, m_group_id;
    Sprite m_Sprite;
};

#endif //ZOMBIEARENA_ENTITY_H
