#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>

#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "Player.h"
#include "NetworkedPlayer.h"
#include "NetworkedMonster.h"
#include "Terrain.h"
#include "Projectile.h"

class Terrain;
class Player;

class Network {

    public:

        sf::IpAddress serverAddress = "127.0.0.1";  // give place to change this in game options
        unsigned short serverPort = 6666;
        int playerID;

        Terrain *terrain;
        Player *player;

        Network();
        ~Network();
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

        void emitProjectile(int pureX, int pureY, std::string direction);
        void updatePlayerLocation(int x, int y, std::string direction);

    private:

        bool requestedPlayers = false;
        bool gotSeed = false;

        std::map<std::string, NetworkedPlayer*> networkPlayers;
        typedef std::map<std::string, NetworkedPlayer*>::iterator i_networkPlayers;

        std::map<std::string, NetworkedMonster*> networkMonsters;
        typedef std::map<std::string, NetworkedMonster*>::iterator i_networkMonsters;
        
        int projCount = 0;
        std::map<std::string, Projectile*> projectiles;
        typedef std::map<std::string, Projectile*>::iterator i_projectiles;

        sf::UdpSocket socket;
        char data[2048];
        std::size_t received;
        unsigned short boundPort;
        float networkTime; // time since last network update
        float lastUpdated; // last time player updated movement

};

#endif // NETWORK_H
