#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>

#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "Client.h"
#include "Dungeon.h"
#include "Monster.h"

class Network {

    public:

        unsigned short port = 6666;
        int serverSeed;

        Network();
        ~Network();

        void run();

    private:
    
        std::map<std::string, Client*> clients;
        typedef std::map<std::string, Client*>::iterator i_clients;

        std::map<std::string, Monster*> monsters;
        typedef std::map<std::string, Monster*>::iterator i_monsters;

        Dungeon* dungeon = nullptr;
    
        sf::UdpSocket socket;

        sf::IpAddress recvAddress;
        unsigned short recvPort;
        char data[2048];
        std::size_t received;
        std::stringstream sendData;

};

#endif // NETWORK_H
