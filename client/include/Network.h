#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>

#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "Player.h"
#include "NetworkedPlayer.h"
#include "Terrain.h"

class Terrain;
class Player;

class Network {

    public:

        sf::IpAddress serverAddress = "127.0.0.1";  // give place to change this in game options
        unsigned short serverPort = 6666;
        int playerID;
        std::string playerName;

        Terrain *terrain;
        Player *player;

        Network();
        ~Network();
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

        int login(std::string pName, unsigned short sPort, sf::IpAddress sAddress){
            playerName = pName; serverPort = sPort; serverAddress = sAddress;
            return 0;
        }
        void updatePlayerLocation(int x, int y, std::string direction);

    private:

        bool requestedPlayers = false;
        bool gotSeed = false;

        std::map<std::string, NetworkedPlayer*> networkPlayers;
        typedef std::map<std::string, NetworkedPlayer*>::iterator i_networkPlayers;

        sf::UdpSocket socket;
        char data[2048];
        std::size_t received;
        unsigned short boundPort;
        float networkTime; // time since last network update
        float lastUpdated; // last time player updated movement

};

#endif // NETWORK_H
