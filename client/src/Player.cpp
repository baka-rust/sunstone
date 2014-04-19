#include "Player.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "Player/Directions.h"
#include "Player/States.h"

Player::Player(int xPos, int yPos, std::string dir) {

    tileX = xPos;
    tileY = yPos;

    x = tileX * 16;
    y = tileY * 16;

    if (dir == "up") {
        direction = N;
    } else if (dir == "down") {
        direction = S;
    } else if (dir == "left") {
        direction = W;
    } else {
        direction = E;
    }
    
    state = Idle;
    
    std::string idleResource = "resources/player/idle";
    int idleFrames = 1;
    float idleSpeed = 1.0;
    
    std::string walkResource = "resources/player/walk";
    int walkFrames = 8;
    float walkSpeed = 0.02  ;
    
    std::string shootResource = "resources/player/fire";
    int shootFrames = 5;
    float shootSpeed = 0.02;
    
    std::string dieResource = "resources/player/die";
    int dieFrames = 98;
    float dieSpeed = 0.05;
    
    // idle
    animations[Idle] = std::vector<AnimationSequence*>(4);
    animations[Idle][N] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][S] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][W] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][E] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    
    // walk
    animations[Walking] = std::vector<AnimationSequence*>(4);
    animations[Walking][N] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][S] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][W] = new AnimationSequence(walkResource + "West", walkFrames, walkSpeed);
    animations[Walking][E] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    
    // shoot
    animations[Firing] = std::vector<AnimationSequence*>(4);
    animations[Firing][N] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][S] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][W] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][E] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    
    // die
    AnimationSequence* dying = new AnimationSequence(dieResource, dieFrames, dieSpeed);
    animations[Dying] = std::vector<AnimationSequence*>(4, dying);
}

void Player::update(float elapsedTime) {
    state = Idle;
    
    if(direction == N || direction == NE || direction == NW) {
        if(y <= (tileY * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            y = y - (speed * elapsedTime);
            animations[Walking][N]->update(elapsedTime);
        }
    }
    else if(direction == S || direction == SE || direction == SW) {
        if(y >= (tileY * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            y = y + (speed * elapsedTime);
            animations[Walking][S]->update(elapsedTime);
        }
    }
    
    if(direction == W || direction == NW || direction == SW) {
        if(x <= (tileX * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            x = x - (speed * elapsedTime);
            animations[Walking][W]->update(elapsedTime);
        }
    }
    else if(direction == E || direction == NE || direction == SE) {
        if(x >= (tileX * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            x = x + (speed * elapsedTime);
            animations[Walking][E]->update(elapsedTime);
        }
    }

    // Handle user input
    if(state != Walking && focused) {
        int dY = 0;
        int dX = 0;
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dY = -1;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dY = 1;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dX = -1;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dX = 1;
        }
        
        if(terrain->getTile(tileX + dX, tileY + dY, "mid") == 0 &&
           (dY != 0 || dX != 0)) {
            tileY = tileY + dY;
            tileX = tileX + dX;
            state = Walking;
            
            if(dY == -1) {
                if(dX == -1) {
                    direction = NW;
                } else if(dX == 1) {
                    direction = NE;
                } else {
                    direction = N;
                }
            } else if(dY == 1) {
                if(dX == -1) {
                    direction = SW;
                } else if(dX == 1) {
                    direction = SE;
                } else {
                    direction = S;
                }
            } else {
                if(dX == -1) {
                    direction = W;
                } else if(dX == 1) {
                    direction = E;
                }
            }
            
            network->updatePlayerLocation(tileX + dX, tileY + dY, "up");
        }
    }
    
    if(state != Walking && onTile) {
        x = tileX * 16;
        y = tileY * 16;
    }

    // set animation positions
    for(auto row : animations) {
        for(auto col : row) {
            col->x = x;
            col->y = y;
        }
    }

}

void Player::draw(sf::RenderWindow *app) {
    Direction tDir;
    if(direction == E || direction == NE || direction == SE) {
        tDir = E;
    } else if(direction == N) {
        tDir = N;
    } else if(direction == S) {
        tDir = S;
    } else {
        tDir = W;
    }
    
    animations[state][tDir]->draw(app);
}
