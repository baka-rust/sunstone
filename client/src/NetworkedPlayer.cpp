#include "NetworkedPlayer.h"

void NetworkedPlayer::setTileX(int x) {
    this->tileX = x;
}

void NetworkedPlayer::setTileY(int y) {
    this->tileY = y;
}

void NetworkedPlayer::setDirection(std::string dir) {
    Direction direction;
    
    if (dir == "up") {
        direction = N;
    } else if (dir == "down") {
        direction = S;
    } else if (dir == "left") {
        direction = W;
    } else {
        direction = E;
    }
    
    this->setDirection(direction);
}

void NetworkedPlayer::setDirection(Direction dir) {
    this->direction = dir;
}