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

void TransformComponent::SetPosition(sf::Vector2f position, float rotation) {
    m_position = position;
    m_Rotation = rotation;
}

void TransformComponent::SetRotation(float rotation) {
    m_Rotation = rotation;
}

float TransformComponent::GetRotation() {
    return m_Rotation;
}
