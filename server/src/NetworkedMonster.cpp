#include "NetworkedMonster.h"

NetworkedMonster::NetworkedMonster(int x, int y, std::string direction) {

	this->x = x;
	this->y = y;
	this->direction = direction;
	this->id = currentId;
	currentId++;

}