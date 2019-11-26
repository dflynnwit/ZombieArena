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
#include "Arena.h"
#include "TextureHolder.h"
#include "Zombie.h"
#include "ZombieHorde.h"
#include "Bullet.h"

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

    /*
     * Windowed
     */
    //Create SFML window
    RenderWindow window(VideoMode(resolution.x/2, resolution.y/2), "Zombie Arena", Style::Default);

    //Create main view
    View mainView(sf::FloatRect(0, 0, resolution.x/2, resolution.y/2));

    /*
     * Fullscreen
     */
//    //Create SFML window
//    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
//
//    //Create main view
//    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //Create texture holder singleton
    TextureHolder textureHolder;

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

    //Create background
    VertexArray background;

    //Load texture for the background
    Texture backgroundTexture = TextureHolder::GetTexture("../Resources/graphics/background_sheet.png");

    //Prepare zombie horde
    int numZombies = 0;
    int numZombiesAlive = 0;
    Zombie* zombies = nullptr;

    //Prepare bullets
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;

    //Tracks time of last shot
    Time lastShot;

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

                if(state == State::PLAYING){
                    //Reloading
                    if(event.key.code == Keyboard::R){
                        if(bulletsSpare >= clipSize){
                            bulletsInClip = clipSize;
                            bulletsSpare -= clipSize;
                        }
                        else if(bulletsSpare > 0){
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                        }
                        else{
                            //Reload failed
                        }
                    }
                }
            }
            //Handle quitting by closing window
            if(event.type == Event::Closed)
                window.close();
        }

        //Handle player input
        if(state == State::PLAYING){
            updatePlayerDirectionalControls(player);

            //Fire bullets
            if(Mouse::isButtonPressed(Mouse::Left)){
                if(gameTimeTotal.asMilliseconds() - lastShot.asMilliseconds() > 1000/fireRate && bulletsInClip > 0){
                    //Pass the player pos and crosshair pos to shoot function
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentBullet %= 100;

                    lastShot = gameTimeTotal;
                    bulletsInClip--;
                }
            }
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

                //Create zombie horde
                numZombies = 10;

                //Delete previously allocated memory
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;

                //Pass vertex array to createbackground
                int tileSize = createBackground(background, arena);

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

            //Convert mouse position to world coords of main view (relative to window for windowed mode)
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(window), mainView);


            //Update player position
            player.update(dtAsSeconds, Mouse::getPosition());

            //Record player new position
            Vector2f playerPosition(player.getCenter());

            //Centre main view on player
            mainView.setCenter(player.getCenter());

            //Update zombies in the horde
            for(int i = 0; i < numZombies; i++){
                if(zombies[i].isAlive())
                    zombies[i].update(dt.asSeconds(), playerPosition);
            }

            //Update bullets in flight
            for(int i = 0; i < 100; i++){
                if(bullets[i].isInFlight())
                    bullets[i].update(dtAsSeconds);
            }
        }

        /*************************************
         * DRAW THE FRAME
         *************************************/
         if(state == State::PLAYING){
             window.clear();

             //Set view to main view
             window.setView(mainView);

             //Draw background
             window.draw(background, &backgroundTexture);

             //Draw player
             window.draw(player.getSprite());

             //Draw zombies
             for(int i = 0; i < numZombies; i++)
                 window.draw(zombies[i].getSprite());

             //Draw bullets
             for(int i = 0; i < 100; i++){
                 if(bullets[i].isInFlight())
                     window.draw(bullets[i].getShape());
             }
         }

         window.display();

    }

    delete[] zombies;
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
