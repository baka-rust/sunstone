#include "Network.h"

Network::Network() {
    socket.setBlocking(false); // just say no to blocking
    socket.bind(sf::Socket::AnyPort);
    boundPort = socket.getLocalPort();

    srand(time(NULL));
    playerID = rand();

    std::stringstream data;
    data.str("3,");
    socket.send(data.str().c_str(), data.str().length(), serverAddress, serverPort);
}

Network::~Network() {
    // send disconnect packet
    socket.unbind();
}

void Network::update(float elapsedTime) {
    sf::IpAddress sender;
    unsigned short port;

    for(i_networkPlayers iterator = networkPlayers.begin(); iterator != networkPlayers.end(); iterator++) {
        iterator->second->update(elapsedTime);
    }

    // join server after grabbing terrain
    if(requestedPlayers == false && gotSeed == true) {
        std::stringstream data;
        data << "1," << playerID << "," << 64 << "," << 64 << "," << "down" << ","; // use a random ID
        socket.send(data.str().c_str(), data.str().length(), serverAddress, serverPort);
        requestedPlayers = true;
    }

    networkTime = networkTime + elapsedTime;
    // account for player timeout
    if(networkTime > 5) {
        networkTime = 0;
        std::stringstream data;
        data << "2," << playerID << "," << player->tileX << "," << player->tileY << "," << player->direction << ",";
        socket.send(data.str().c_str(), data.str().length(), serverAddress, serverPort);
    }

    if(socket.receive(data, 2048, received, sender, port) != sf::Socket::NotReady) {
        std::vector<std::string> receivedArray;

        std::stringstream currentSplit;
        for(unsigned int i=0; i < received; i++) {
            if(data[i] == ',') {
                receivedArray.push_back(currentSplit.str());
                currentSplit.str("");
            }
            else {
                currentSplit << data[i];
            }
        }

        if(receivedArray.size() > 0) {

            if(receivedArray[0] == "1") {
                // join
                // 1,{name},{x},{y},{direction},{type},
                std::istringstream convertX(receivedArray[2]);
                std::stringstream convertY(receivedArray[3]);
                int x;
                int y;
                convertX >> x;
                convertY >> y;
				if(receivedArray[5] == "0") {
					// player
					if(networkPlayers.find(receivedArray[1]) == networkPlayers.end()) {
						networkPlayers[receivedArray[1]] = new NetworkedPlayer(x, y, receivedArray[4]);
						std::cout << "added new player " << receivedArray[1] << " at " << x << ", " << y << " facing " << receivedArray[4] << std::endl;
					}
				}
				else if(receivedArray[5] == "1") {
					// monster
				}
            }

            else if(receivedArray[0] == "2") {
                // movement update
                // 2,{name},{x},{y},{direction},
                std::istringstream convertX(receivedArray[2]);
                std::istringstream convertY(receivedArray[3]);
                int x;
                int y;
                convertX >> x;
                convertY >> y;
                if(!(networkPlayers.find(receivedArray[1]) == networkPlayers.end())) {
                    std::cout << "updated " << receivedArray[1] << " at " << x << ", " << y << " facing " << receivedArray[4] << std::endl;
                    networkPlayers[receivedArray[1]]->tileX = x;
                    networkPlayers[receivedArray[1]]->tileY = y;
                    networkPlayers[receivedArray[1]]->direction = receivedArray[4];
                }
            }

            else if(receivedArray[0] == "3") {
                // seed response
                // 3,{seed},
                std::istringstream convertSeed(receivedArray[1]);
                int seed;
                convertSeed >> seed;
                std::cout << "got seed " << seed << std::endl;
                terrain->generateFromSeed(seed);
                gotSeed = true;
            }

        }
    }
}

void Network::draw(sf::RenderWindow *app) {
    for(i_networkPlayers iterator = networkPlayers.begin(); iterator != networkPlayers.end(); iterator++) {
        iterator->second->draw(app);
    }
}


void Network::updatePlayerLocation(int x, int y, std::string direction) {

    std::stringstream data;
    data << "2," << playerID << "," << x << "," << y << "," << direction << ",";
    socket.send(data.str().c_str(), data.str().length(), serverAddress, serverPort);

}
