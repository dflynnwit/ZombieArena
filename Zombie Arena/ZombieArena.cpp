//
//  main.cpp
//  delete
//
//  Created by admin on 14/10/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "TextureHolder.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Pickup.h"
#include "MazeGenerator.h"
#include "Flashlight.h"
#include "Key.h"
#include "ExitTerminal.h"

void updatePlayerDirectionalControls(Player &p);

using namespace sf;

int main(int argc, const char * argv[]) {
    //Possible game states
    enum class State {PAUSED, LEVELING_UP, GAME_OVER, PLAYING};

    //Start in GAME OVER state
    State state = State::GAME_OVER;

    //Get screen resolution for SFML window
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;

    Vector2f resolution(screenResolution.x, screenResolution.y);

    /*
     * Windowed
     */
    //Create SFML window
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Default);

    //Create main view
    View mainView(sf::FloatRect(0, 0, 1280, 720));

    /*
     * Fullscreen
     */
    //Create SFML window
//    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
//
//    //Create main view
//    View mainView(sf::FloatRect(0, 0, 1280, 720));

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

    //Prep maze generator
    MazeGenerator mazeGenerator(.2);

    //Store walls
    std::vector<Tile>* walls = nullptr;
    //And floor tiles
    std::vector<Tile>* floor = nullptr;

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

    //Create some pickups
    std::vector<Pickup*> healthPickups;
    std::vector<Pickup*> ammoPickups;

    //Store keys
    std::vector<Key*> keys;
    int keysCollected = 0;
    int keysNeeded = 2;

    //Prepare exit object
    ExitTerminal* exit = nullptr;

    //Prepare bullets
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;

    //Tracks time of last shot
    Time lastShot;

    //Hide cursor in game and display crosshair
    window.setMouseCursorVisible(false);
    Sprite crosshairSprite;
    crosshairSprite.setTexture(TextureHolder::GetTexture("../Resources/graphics/crosshair.png"));
    crosshairSprite.setOrigin(25, 25);

    //Prep flashlight shape
    Flashlight flashlight(window);

    //init game score
    int score = 0;
    int hiScore = 0;

    //Prep menu screens
    Sprite gameOverSprite;

    Texture gameOverTexture = TextureHolder::GetTexture("../Resources/graphics/background.png");
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(0, 0);

    //Scale the bg image
    gameOverSprite.setScale(resolution.x/1920, resolution.y/1080);

    //Create HUD view
    View hudView(FloatRect(0, 0, resolution.x, resolution.y));

    //Create hud icons
    //Ammo
    Sprite ammoIconSprite;
    Texture ammoIconTexture = TextureHolder::GetTexture("../Resources/graphics/ammo_icon.png");
    ammoIconSprite.setTexture(ammoIconTexture);
    ammoIconSprite.setPosition(20, resolution.y - 200);

    //Prep game font
    Font font;
    font.loadFromFile("../Resources/fonts/zombiecontrol.ttf");

    //Pause text
    Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(155);
    pausedText.setFillColor(Color::White);
    pausedText.setString("Press ENTER \nto continue");

    //Center pause text
    FloatRect pauseRect = pausedText.getLocalBounds();
    pausedText.setOrigin(pauseRect.left + pauseRect.width/2.0f, pauseRect.top + pauseRect.height/2.0f);
    pausedText.setPosition(resolution.x/2, resolution.y/2);

    // Game Over
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(125);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("Press Enter to play");

    FloatRect gameOverRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverRect.left+gameOverRect.width/2.0f, gameOverRect.top+gameOverRect.height/2.0f);
    gameOverText.setPosition(resolution.x/2, resolution.y/2);

    // Levelling up
    Text levelUpText;
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(80);
    levelUpText.setFillColor(Color::White);
    levelUpText.setPosition(150, 250);
    std::stringstream levelUpStream;
    levelUpStream <<
                  "1- Increased rate of fire" <<
                  "\n2- Increased clip size(next reload)" <<
                  "\n3- Increased max health" <<
                  "\n4- Increased run speed" <<
                  "\n5- More and better health pickups" <<
                  "\n6- More and better ammo pickups";
    levelUpText.setString(levelUpStream.str());

    FloatRect levelUpRect = levelUpText.getLocalBounds();
    levelUpText.setOrigin(levelUpRect.left+levelUpRect.width/2.0f, levelUpRect.top+levelUpRect.height/2.0f);
    levelUpText.setPosition(resolution.x/2, resolution.y/2);

    // Ammo
    Text ammoText;
    ammoText.setFont(font);
    ammoText.setCharacterSize(55);
    ammoText.setFillColor(Color::White);
    ammoText.setPosition(200, resolution.y-200);

    // Score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 0);

    //Load hi score from file
    std::ifstream inputFile("../Resources/gamedata/scores.txt");
    if(inputFile.is_open()){
        inputFile >> hiScore;
        inputFile.close();
    }

    // Hi Score
    Text hiScoreText;
    hiScoreText.setFont(font);
    hiScoreText.setCharacterSize(55);
    hiScoreText.setFillColor(Color::White);
    hiScoreText.setPosition(resolution.x-400, 0);
    std::stringstream s;
    s << "Hi Score:" << hiScore;
    hiScoreText.setString(s.str());

    // Zombies remaining
    Text keysCollectedText;
    keysCollectedText.setFont(font);
    keysCollectedText.setCharacterSize(55);
    keysCollectedText.setFillColor(Color::White);
    keysCollectedText.setPosition(resolution.x - 400, resolution.y - 200);
    keysCollectedText.setString("Keys: 0");

    // Wave number
    int wave = 0;
    Text waveNumberText;
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(Color::White);
    waveNumberText.setPosition(resolution.x*0.66, resolution.y-200);
    waveNumberText.setString("Wave: 0");

    // Health bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(resolution.x*0.33, resolution.y-200);

    //Time since last HUD update
    int framesSinceLastHUDUpdate = 0;

    //HUD update frequency (in frames)
    int fpsMeasurementFrameInterval = 1000;

    //Prep sound buffers
    SoundBuffer hitBuffer;
    hitBuffer.loadFromFile("../Resources/sound/hit.wav");
    Sound hit;
    hit.setBuffer(hitBuffer);

    // Prepare the splat sound
    SoundBuffer splatBuffer;
    splatBuffer.loadFromFile("../Resources/sound/splat.wav");
    sf::Sound splat;
    splat.setBuffer(splatBuffer);

    // Prepare the shoot sound
    SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("../Resources/sound/shoot.wav");
    Sound shoot;
    shoot.setBuffer(shootBuffer);

    // Prepare the reload sound
    SoundBuffer reloadBuffer;
    reloadBuffer.loadFromFile("../Resources/sound/reload.wav");
    Sound reload;
    reload.setBuffer(reloadBuffer);

    // Prepare the failed sound
    SoundBuffer reloadFailedBuffer;
    reloadFailedBuffer.loadFromFile("../Resources/sound/reload_failed.wav");
    Sound reloadFailed;
    reloadFailed.setBuffer(reloadFailedBuffer);

    // Prepare the powerup sound
    SoundBuffer powerupBuffer;
    powerupBuffer.loadFromFile("../Resources/sound/powerup.wav");
    Sound powerup;
    powerup.setBuffer(powerupBuffer);

    // Prepare the pickup sound
    SoundBuffer pickupBuffer;
    pickupBuffer.loadFromFile("../Resources/sound/pickup.wav");
    Sound pickup;
    pickup.setBuffer(pickupBuffer);

    //Prepare keycard sound
    SoundBuffer keycardBuffer;
    keycardBuffer.loadFromFile("../Resources/sound/keycard.ogg");
    Sound keycardSound;
    keycardSound.setBuffer(keycardBuffer);

    //Prepare terminal sounds
    SoundBuffer alarmBuffer;
    alarmBuffer.loadFromFile("../Resources/sound/alarm.ogg");
    Sound alarm;
    alarm.setBuffer(alarmBuffer);

    SoundBuffer keyboardClackBuffer;
    keyboardClackBuffer.loadFromFile("../Resources/sound/keyboard.ogg");
    Sound keyboardClack;
    keyboardClack.setBuffer(keyboardClackBuffer);


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
                    } else if (state == State::GAME_OVER) {
                        score = 0;
                        wave = 0;

                        currentBullet = 0;
                        bulletsSpare = 24;
                        bulletsInClip = 6;
                        clipSize = 6;
                        fireRate = 1;

                        player.resetPlayerStats();

                        state = State::LEVELING_UP;
                    }
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
                            reload.play();
                        }
                        else if(bulletsSpare > 0){
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                            reload.play();
                        }
                        else{
                            //Reload failed
                            reloadFailed.play();
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
                    shoot.play();
                }
            }
        }

        //Handle level up screen
        if(state == State::LEVELING_UP){
            switch (event.key.code){
                case Keyboard::Num1:
                    fireRate++;
                    state = State::PLAYING;
                    break;
                case Keyboard::Num2:
                    clipSize+=clipSize;
                    state = State::PLAYING;
                    break;
                case Keyboard::Num3:
                    player.upgradeHealth();
                    state = State::PLAYING;
                    break;
                case Keyboard::Num4:
                    player.upgradeSpeed();
                    state = State::PLAYING;
                    break;
                case Keyboard::Num5:
//                    healthPickup.upgrade();
                    state = State::PLAYING;
                    break;
                case Keyboard::Num6:
//                    ammoPickup.upgrade();
                    state = State::PLAYING;
                    break;
            }

            if(state == State::PLAYING){
                ///********************
                /// Prepare the level
                ///********************
                delete(walls);
                delete(floor);
                delete[] zombies;

                ammoPickups.clear();
                healthPickups.clear();
                keys.clear();

                keysCollected = 0;

                wave++;

                int difficulty = wave * 5;

                arena.width = 500 * wave;
                arena.height = 500 * wave;
                arena.left = 0;
                arena.top = 0;

                mazeGenerator.GenerateMazeData(10 + difficulty, 10 + difficulty, difficulty, keysNeeded);
                walls = mazeGenerator.CreateMaze();
                floor = mazeGenerator.GetFloor();

                std::vector<std::vector<int>> mazeData = mazeGenerator.GetData();

                for(int i = 0; i < mazeData.size(); i++){
                    for(int j = 0; j < mazeData[0].size(); j++){
                        switch(mazeData[i][j]) {
                            case 2: //Medkit
                                healthPickups.push_back(new Pickup(Pickup::HEALTH, Vector2f(j * 64, i * 64)));
                                break;
                            case 3: //Ammo
                                ammoPickups.push_back(new Pickup(Pickup::AMMO, Vector2f(j * 64, i * 64)));
                                break;
                            case 4: //Enemy
                                break;
                            case 5: //Player spawn
                                player.spawn(j * 64, i * 64, resolution);
                                break;
                            case 6: //Exit
                                exit = new ExitTerminal(j * 64, i * 64);
                                break;
                            case 7: //Key
                                keys.push_back(new Key(j * 64, i * 64));
                                break;
                        }
                    }
                }

                numZombiesAlive = difficulty;

                //play upgrade sound
                powerup.play();

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
            player.update(dtAsSeconds, Mouse::getPosition(), *walls);

            //Record player new position
            Vector2f playerPosition(player.getCenter());

            //Centre main view on player
            mainView.setCenter(player.getCenter());

            //Update zombies in the horde
            for(int i = 0; i < numZombies; i++){
                if(zombies[i].isAlive())
                    zombies[i].update(dt.asSeconds(), playerPosition, *walls);
            }

            //Update exit terminal
            exit->Update(dt.asSeconds());

            if(exit->Collision(player)) {
                bool exitActive = exit->ActivateExit(keysCollected == keysNeeded);
                if(exitActive) {
                    if (keyboardClack.getStatus() != 2)
                        keyboardClack.play();
                }
                else if(alarm.getStatus() != 2)
                    alarm.play();
            }

            //Update bullets in flight
            for(auto & bullet : bullets){
                if(bullet.isInFlight()){
                    bullet.update(dtAsSeconds);
                    //Check bullets collision against zombies
                    for (int j = 0; j < numZombies; j++) {
                        if (zombies[j].isAlive()) {
                            if (bullet.Collision(zombies[j])) {
                                // Stop the bullet
                                bullet.stop();

                                // Register the hit and see if it was a kill
                                if (zombies[j].hit()) {
                                    // Not just a hit but a kill too
                                    splat.play();
                                    score += 10;
                                    if (score >= hiScore) {
                                        hiScore = score;
                                    }

                                    numZombiesAlive--;

                                    // When all the zombies are dead (again)
                                    if (numZombiesAlive == 0) {
                                        state = State::LEVELING_UP;
                                    }
                                }
                            }
                        }
                    }

                    //Check bullets collision against walls
                    for(auto wall : *walls)
                        if(bullet.Collision(wall))
                            bullet.stop();

                }
            }

            //Update crosshair
            crosshairSprite.setPosition(mouseWorldPosition.x, mouseWorldPosition.y);

            //Update flashlight
            flashlight.Update(player.getCenter(), player.getRotation());

            // Have any zombies touched the player?
            for (int i = 0; i < numZombies; i++)
            {
                if(zombies[i].isAlive() && zombies[i].Collision(player)) {
//                std::cout << "Player collided with zombie" << std::endl;
                    if (player.hit(gameTimeTotal)) {
                        //Get hit effect
                        hit.play();

                        if(player.getHealth() <= 0) {
                            state = State::GAME_OVER;

                            std::ofstream outputFile("../Resources/gamedata/scores.txt");
                            outputFile << hiScore;
                            outputFile.close();
                        }

                    }
                }
            }// End player touched

            //Pickup collisions
            //Health
            for(auto hp : healthPickups){
                if(hp->isSpawned() && player.Collision(*hp)){
                    player.increaseHealthLevel(hp->gotIt());
                    pickup.play();
                }
            }

            //Ammo
            for(auto ammo : ammoPickups){
                if(ammo->isSpawned() && player.Collision(*ammo)){
                    bulletsSpare += ammo->gotIt();
                    reload.play();
                }
            }

            //Keycards
            for(auto k : keys){
                if(!k->isCollected() && player.Collision(*k)){
                    k->Collect();
                    keysCollected++;
                    keycardSound.play();
                }
            }

            //Update healthbar
            healthBar.setSize(Vector2f(player.getHealth()*3, 70));

            framesSinceLastHUDUpdate++;

            //Calculate FPS every 1k frames
            if(framesSinceLastHUDUpdate > fpsMeasurementFrameInterval){
                std::stringstream ssAmmo, ssScore, ssHiScore, ssWave, ssKeysCollected;

                ssAmmo << bulletsInClip << "/" << bulletsSpare;
                ammoText.setString(ssAmmo.str());

                ssScore << "Score: " << score;
                scoreText.setString(ssScore.str());

                ssHiScore << "Hi Score: " <<  hiScore;
                hiScoreText.setString(ssHiScore.str());

                ssWave << "Wave: " << wave;
                waveNumberText.setString(ssWave.str());

                ssKeysCollected << "Keys: " << keysCollected << "/" << keysNeeded;
                keysCollectedText.setString(ssKeysCollected.str());

                framesSinceLastHUDUpdate = 0;

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
            for(auto tile : *floor)
                if(player.Distance(tile) < 300)
                    tile.Draw(window);

            //Draw pickups
            for(auto p : healthPickups)
                if(p->Distance(player) < 300) {
                    p->draw(window);
                }
            for(auto p : ammoPickups)
                if(p->Distance(player) < 300)
                    p->draw(window);

            for(auto k: keys)
                if(k->Distance(player) < 300)
                    k->Draw(window);

            //Draw exit terminal
            if(exit->Collision(player) < 300)
                exit->Draw(window);

            //Draw zombies
            for(int i = 0; i < numZombies; i++)
                if(zombies[i].Distance(player) < 300)
                    zombies[i].draw(window);

            //Draw player
            player.draw(window);

            //Draw bullets
            for(int i = 0; i < 100; i++){
                bullets[i].draw(window);
            }

            //Draw walls
            for(auto wall : *walls) {
                if(player.Distance(wall) < 300)
                    wall.Draw(window);
            }

            //Draw flashlight effect
            window.draw(flashlight);

            //Draw crosshair
            window.draw(crosshairSprite);

            window.setView(hudView);

            window.draw(ammoIconSprite);
            window.draw(ammoText);
            window.draw(scoreText);
            window.draw(hiScoreText);
            window.draw(healthBar);
            window.draw(waveNumberText);
            window.draw(keysCollectedText);
        }
        else if(state == State::LEVELING_UP){
            window.draw(gameOverSprite);
            window.draw(levelUpText);
        }
        else if(state == State::PAUSED){
            window.draw(pausedText);
        }
        else if(state == State::GAME_OVER){
            window.draw(gameOverSprite);
            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(hiScoreText);
        }


        window.display();
    }

    delete[] zombies;
    delete walls;
    delete floor;
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
