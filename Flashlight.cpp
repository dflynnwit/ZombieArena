//
// Created by Pokora on 29/12/2019.
//

#include "Flashlight.h"

Flashlight::Flashlight(RenderWindow &window) {
    int y = window.getSize().y;
    int x = window.getSize().x;

    m_vshape.setPrimitiveType(TriangleFan);
    m_vshape.resize(5);

    m_vshape[0].position = sf::Vector2f(12, 0);
    m_vshape[0].color = sf::Color(0,0,0,240);

    m_vshape[1].position = sf::Vector2f(x, y);
    m_vshape[1].color = sf::Color(0,0,0,255);

    m_vshape[2].position = sf::Vector2f(- x, y);
    m_vshape[2].color = sf::Color(0,0,0,255);

    m_vshape[3].position = sf::Vector2f(- x, - y);
    m_vshape[3].color = sf::Color(0,0,0,255);

    m_vshape[4].position = sf::Vector2f(x, - y);
    m_vshape[4].color = sf::Color(0,0,0,255);
}

void Flashlight::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_vshape, states);
}

void Flashlight::Update(Vector2f playerPosition, float rotation) {
    this->setPosition(playerPosition);
    this->setRotation(rotation);
    this->setScale(1.1,1.1);
}
