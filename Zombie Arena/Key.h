//
// Created by Pokora on 02/01/2020.
//

#ifndef ZOMBIEARENA_KEY_H
#define ZOMBIEARENA_KEY_H

#include "Entity.h"

class Key : public Entity {
private:
    bool m_collected;
public:
    Key(int x, int y);

    void Collect();

    bool isCollected();

    void Draw(RenderWindow& window);
};


#endif //ZOMBIEARENA_KEY_H
