//
//  main.cpp
//  delete
//
//  Created by admin on 14/10/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"

void updatePlayerDirectionalControls(Player &p);

using namespace sf;

int main(int argc, const char * argv[]) {
    //Possible game states
    enum class State {PAUSED, LEVELING_UP, GAME_OVER, PLAYING};

    //Start in GAME OVER state
    State state = State ::GAME_OVER;

    //Get screen resolution for SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    //Create SFML window
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

    //Create main view
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //Prepare game clock
    Clock clock;

    //How long are we playing
    Time gameTimeTotal;

    //Mouse position relative to world coords
    Vector2f mouseWorldPosition;

    //Mouse position relative to screen coords
    Vector2i mouseScreenPosition;

    //Create player instance
    Player player;

    //Arena boundaries
    IntRect arena;

    //Main game loop
    while(window.isOpen()){
        /*
         * HANDLE INPUT
         */

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::KeyPressed) {
                //Handle return key - PAUSE, RESUME
                if (event.key.code == Keyboard::Return) {
                    if (state == State::PLAYING)
                        state = State::PAUSED;
                    else if (state == State::PAUSED) {
                        state = State::PLAYING;
                        //restart the clock to avoid frame jumps
                        clock.restart();
                    } else if (state == State::GAME_OVER)
                        state = State::LEVELING_UP;
                }

                //Handle quitting by esc
                if(event.key.code == Keyboard::Escape)
                    window.close();
            }
            //Handle quitting by closing window
            if(event.type == Event::Closed)
                window.close();

            //Handle player input
            if(state == State::PLAYING){
                updatePlayerDirectionalControls(player);
            }

        }
    }

    return 0;
}

void updatePlayerDirectionalControls(Player &p){
    p.setMoveDown(Keyboard::isKeyPressed(Keyboard::Down));
    p.setMoveLeft(Keyboard::isKeyPressed(Keyboard::Left));
    p.setMoveRight(Keyboard::isKeyPressed(Keyboard::Right));
    p.setMoveUp(Keyboard::isKeyPressed(Keyboard::Up));
}
