//
// Created by Pokora on 29/12/2019.
//

#ifndef ZOMBIEARENA_FLASHLIGHT_H
#define ZOMBIEARENA_FLASHLIGHT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Flashlight {
private:
    Vector2f m_position;
    float m_rotation;
    ConvexShape m_shape;
public:
    Flashlight();
    void Draw(RenderWindow& window, Vector2f playerPosition, float playerRotation);
};


#endif //ZOMBIEARENA_FLASHLIGHT_H
