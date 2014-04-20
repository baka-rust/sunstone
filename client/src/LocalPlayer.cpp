#include "LocalPlayer.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "Player/Directions.h"
#include "Player/States.h"

void LocalPlayer::update(float elapsedTime) {
    // Handle user input
    if(state != Walking && focused) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && focused) {
            if(terrain->getTile(tileX, tileY-1, "mid") == 0) {
                tileY = tileY - 1;
                state = Walking;
            }
            
            direction = N;
            network->updatePlayerLocation(tileX, tileY, "up");
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(terrain->getTile(tileX, tileY+1, "mid") == 0) {
                tileY = tileY + 1;
                state = Walking;
            }
            
            direction = S;
            network->updatePlayerLocation(tileX, tileY, "down");
            
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(terrain->getTile(tileX-1, tileY, "mid") == 0) {
                tileX = tileX - 1;
                state = Walking;
            }
            
            direction = W;
            network->updatePlayerLocation(tileX, tileY, "down");
            
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if(terrain->getTile(tileX+1, tileY, "mid") == 0) {
                tileX = tileX + 1;
                state = Walking;
            }
            
            direction = E;
            network->updatePlayerLocation(tileX, tileY, "right");
            
        }
    }
}