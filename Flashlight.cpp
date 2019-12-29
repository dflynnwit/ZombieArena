//
// Created by Pokora on 29/12/2019.
//

#include "Flashlight.h"

Flashlight::Flashlight(RenderWindow &window) {
    //Decrease size to 60% of screen width to avoid blank spots but retain quick gradient
    int x = window.getSize().x/10*6;

    //Flashlight
    m_flashlightVA.setPrimitiveType(TriangleFan);
    m_flashlightVA.resize(7);

    m_flashlightVA[0].position = sf::Vector2f(12, 0);
    m_flashlightVA[0].color = sf::Color(0, 0, 0, 240);

    m_flashlightVA[1].position = sf::Vector2f(x, x / 2);
    m_flashlightVA[1].color = sf::Color(0, 0, 0, 255);

    m_flashlightVA[2].position = sf::Vector2f(x, x);
    m_flashlightVA[2].color = sf::Color(0, 0, 0, 255);

    m_flashlightVA[3].position = sf::Vector2f(- x, x);
    m_flashlightVA[3].color = sf::Color(0, 0, 0, 255);

    m_flashlightVA[4].position = sf::Vector2f(- x, - x);
    m_flashlightVA[4].color = sf::Color(0, 0, 0, 255);

    m_flashlightVA[5].position = sf::Vector2f(x, - x);
    m_flashlightVA[5].color = sf::Color(0, 0, 0, 255);

    m_flashlightVA[6].position = sf::Vector2f(x, - x / 2);
    m_flashlightVA[6].color = sf::Color(0, 0, 0, 255);


    //Laser pointer
    m_laserVA.setPrimitiveType(Lines);
    m_laserVA.resize(2);

    m_laserVA[0].position = Vector2f(15, 0);
    m_laserVA[0].color = Color(255, 50, 0, 200);

    m_laserVA[1].position = Vector2f(x, 0);
    m_laserVA[1].color = Color(255, 50, 0, 10);
}

void Flashlight::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_flashlightVA, states);
    target.draw(m_laserVA, states);
}

void Flashlight::Update(Vector2f playerPosition, float rotation) {
    this->setPosition(playerPosition);
    this->setRotation(rotation);
}
