#include "NetworkedPlayer.h"

void NetworkedPlayer::setTileX(int x) {
    this->tileX = x;
}

void NetworkedPlayer::setTileY(int y) {
    this->tileY = y;
}

void NetworkedPlayer::setDirection(std::string dir) {
    this->setDirection(stringToDirection(dir));
}

void NetworkedPlayer::setDirection(Direction dir) {
    this->direction = dir;
}