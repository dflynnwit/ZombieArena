//
// Created by Pokora on 02/01/2020.
//

#ifndef ZOMBIEARENA_EXITTERMINAL_H
#define ZOMBIEARENA_EXITTERMINAL_H


#include "Tile.h"

class ExitTerminal : public Entity{
private:
    const int SCREEN_TIME = 3;
    float m_TimeSinceActivation;
    bool m_counting;
    bool m_denied;

public:
    ExitTerminal(int x, int y);
    void Update(float elapsedTime);
    bool ActivateExit(bool hasEnoughKeys);
};


#endif //ZOMBIEARENA_EXITTERMINAL_H
