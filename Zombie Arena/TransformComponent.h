//
// Created by pokor on 14/12/2020.
//

#ifndef ZOMBIEARENA_TRANSFORMCOMPONENT_H
#define ZOMBIEARENA_TRANSFORMCOMPONENT_H


#include <SFML/Graphics.hpp>
#include "Component.h"

class TransformComponent : public Component{
public:
    TransformComponent();
    void SetPosition(sf::Vector2f position);
    void SetPosition(sf::Vector2f position, float rotation);
    void SetRotation(float rotation);
    sf::Vector2f&  GetPosition();
    float GetRotation();
private:
    sf::Vector2f  m_position;
    float m_Rotation;
};


#endif