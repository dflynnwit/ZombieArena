//
// Created by pokor on 14/12/2020.
//

#include <iostream>
#include "TransformComponent.h"

TransformComponent::TransformComponent() :
        m_position({ 0.f, 0.f })
{
}
void TransformComponent::SetPosition(sf::Vector2f position)
{
    m_position = position;
}
sf::Vector2f& TransformComponent::GetPosition()
{
    return m_position;
}