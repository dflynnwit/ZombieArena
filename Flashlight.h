//
// Created by Pokora on 29/12/2019.
//

#ifndef ZOMBIEARENA_FLASHLIGHT_H
#define ZOMBIEARENA_FLASHLIGHT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Flashlight : public Drawable, public Transformable{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    VertexArray m_vshape;
public:
    Flashlight(RenderWindow& window);

    void Update(Vector2f playerPosition, float rotation);
};


#endif //ZOMBIEARENA_FLASHLIGHT_H
