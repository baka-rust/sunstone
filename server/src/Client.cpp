#include "Client.h"

Client::Client(sf::IpAddress ip, unsigned short port, std::string name, int x, int y, std::string direction) {
    this->ip = ip;
    this->port = port;
    this->name = name;
    this->x = x;
    this->y = y;
    this->direction = direction;
}
