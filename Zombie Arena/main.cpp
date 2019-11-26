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
    State state = State::GAME_OVER;

    //Get screen resolution for SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    //Create SFML window
    RenderWindow window(VideoMode(resolution.x/2, resolution.y/2), "Zombie Arena", Style::Default);

    //Create main view
    View mainView(sf::FloatRect(0, 0, resolution.x/2, resolution.y/2));

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
        /*************************************
         * HANDLE INPUT
         *************************************/

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
        }

        //Handle player input
        if(state == State::PLAYING){
            updatePlayerDirectionalControls(player);
        }

        //Handle level up screen
        if(state == State::LEVELING_UP){
            switch (event.key.code){
                case Keyboard::Num1:
                    state = State::PLAYING;
                    break;
                case Keyboard::Num2:
                    state = State::PLAYING;
                    break;
                case Keyboard::Num3:
                    state = State::PLAYING;
                    break;
                case Keyboard::Num4:
                    state = State::PLAYING;
                    break;
                case Keyboard::Num5:
                    state = State::PLAYING;
                    break;
                case Keyboard::Num6:
                    state = State::PLAYING;
                    break;
            }

            if(state == State::PLAYING){
                // Prepare the level
                // We will modify the next two lines later
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                // We will modify this line of code later
                int tileSize = 50;

                // Spawn the player in the middle of the arena
                player.spawn(arena, resolution, tileSize);

                // Reset the clock so there isn't a frame jump
                clock.restart();
            }
        }

        /*************************************
         * UPDATE THE FRAME
         *************************************/
        if(state == State::PLAYING){
            //Update delta time
            Time dt = clock.restart();

            //Update total time
            gameTimeTotal += dt;

            //Make a decimal fraction of 1 from the delta time -- What the hell does this mean ?
            float dtAsSeconds = dt.asSeconds();

            //Get mouse pointer position
            mouseScreenPosition = Mouse::getPosition(window);

            //Convert mouse position to world coords of main view
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            //Update player position
            player.update(dtAsSeconds, Mouse::getPosition());

            //Record player new position
            Vector2f playerPosition(player.getCenter());

            //Centre main view on player
            mainView.setCenter(player.getCenter());
        }

        /*************************************
         * DRAW THE FRAME
         *************************************/
         if(state == State::PLAYING){
             window.clear();

             //Set view to main view
             window.setView(mainView);

             //Draw player
             window.draw(player.getSprite());
         }

         window.display();

    }

    return 0;
}

void updatePlayerDirectionalControls(Player &p){
    p.setMoveDown(Keyboard::isKeyPressed(Keyboard::Down) ||
                          Keyboard::isKeyPressed(Keyboard::S));
    p.setMoveLeft(Keyboard::isKeyPressed(Keyboard::Left) ||
                          Keyboard::isKeyPressed(Keyboard::A));
    p.setMoveRight(Keyboard::isKeyPressed(Keyboard::Right) ||
                           Keyboard::isKeyPressed(Keyboard::D));
    p.setMoveUp(Keyboard::isKeyPressed(Keyboard::Up) ||
                        Keyboard::isKeyPressed(Keyboard::W));
}
