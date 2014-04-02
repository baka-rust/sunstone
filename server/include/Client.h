#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>

#include <string>

class Client {

    public:

        int x, y;
        std::string direction;
        std::string name;

        sf::IpAddress ip;
        unsigned short port;

        Client(sf::IpAddress ip, unsigned short port, std::string name, int x, int y, std::string direction);

};

#endif // CLIENT_H
