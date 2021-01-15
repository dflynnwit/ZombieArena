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
    sf::Vector2f&  GetPosition();
private:
    sf::Vector2f  m_position;
};


#endif