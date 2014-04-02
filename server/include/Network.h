#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>

#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "Client.h"

class Network {

    public:

        unsigned short port = 666;
        int serverSeed;

        Network();
        ~Network();

        void run();

    private:

        std::map<std::string, Client*> clients;
        typedef std::map<std::string, Client*>::iterator i_clients;

        sf::UdpSocket socket;

        sf::IpAddress recvAddress;
        unsigned short recvPort;
        char data[2048];
        std::size_t received;
        std::stringstream sendData;

};

#endif // NETWORK_H
