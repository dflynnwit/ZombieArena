//
// Created by Pokora on 29/12/2019.
//

#include "Flashlight.h"

Flashlight::Flashlight() {
    m_shape.setPointCount(6);

    // define the points
    m_shape.setPoint(0, sf::Vector2f(12, 0));
    m_shape.setPoint(1, sf::Vector2f(1500, 1000));
    m_shape.setPoint(2, sf::Vector2f(1500, 2000));
    m_shape.setPoint(3, sf::Vector2f(-1500, 2000));
    m_shape.setPoint(4, sf::Vector2f(-1500, -2000));
    m_shape.setPoint(5, sf::Vector2f(1500, -1000));

    //Set outside color
    m_shape.setFillColor(Color(0, 0, 0, 240));
}

void Flashlight::Draw(RenderWindow &window, Vector2f playerPosition, float playerRotation) {
    m_shape.setPosition(playerPosition);
    m_shape.setRotation(playerRotation);
    window.draw(m_shape);
}
