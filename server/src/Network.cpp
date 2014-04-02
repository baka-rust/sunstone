#include "Network.h"

Network::Network() {

    socket.setBlocking(false);
    socket.bind(port);

    srand(time(NULL));
    serverSeed = rand() % 9999;

    std::cout << "current seed " << serverSeed << std::endl;

}

Network::~Network() {
    socket.unbind();
}

void Network::run() {

    while(true) {
        if(socket.receive(data, 2048, received, recvAddress, recvPort) != sf::Socket::NotReady) {

            std::vector<std::string> receivedArray;

            std::stringstream currentSplit;
            for(unsigned int i = 0; i < received; i++) {
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
                    // 1,{name},{x},{y},{direction},
                    std::istringstream convertX(receivedArray[2]);
                    std::istringstream convertY(receivedArray[3]);
                    int x;
                    int y;
                    convertX >> x;
                    convertY >> y;
                    if(clients.find(receivedArray[1]) == clients.end()) {
                        clients[receivedArray[1]] = new Client(recvAddress, recvPort, receivedArray[1], x, y, receivedArray[4]);

                        // tell other players about new one
                        sendData.str(std::string()); // clear it
                        sendData << "1," << receivedArray[1] << "," << x << "," << y << "," << receivedArray[4] << ",";
                        for(i_clients iterator = clients.begin(); iterator != clients.end(); iterator++) {
                            Client *client = iterator->second;
                            if(client->name != receivedArray[1]) {
                                socket.send(sendData.str().c_str(), sendData.str().length(), client->ip, client->port);
                            }
                        }

                        // tell it about other players
                        for(i_clients iterator = clients.begin(); iterator != clients.end(); iterator++) {
                            Client *client = iterator->second;
                            if(client->name != receivedArray[1]) {
                                sendData.str(std::string()); // clear it
                                sendData << "1," << client->name << "," << client->x << "," << client->y << "," << client->direction << ",";
                                socket.send(sendData.str().c_str(), sendData.str().length(), recvAddress, recvPort);
                            }
                        }

                        std::cout << "added new player " << receivedArray[1] << " at " << x << ", " << y << " facing " << receivedArray[4] << std::endl;
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
                    if(!(clients.find(receivedArray[1]) == clients.end())) {
                        std::cout << "updated " << receivedArray[1] << " at " << x << ", " << y << " facing " << receivedArray[4] << std::endl;
                        clients[receivedArray[1]]->x = x;
                        clients[receivedArray[1]]->y = y;
                        clients[receivedArray[1]]->direction = receivedArray[4];

                        sendData.str(std::string()); // clear it
                        sendData << "2," << receivedArray[1] << "," << x << "," << y << "," << receivedArray[4] << ",";
                        for(i_clients iterator = clients.begin(); iterator != clients.end(); iterator++) {
                            Client *client = iterator->second;
                            if(client->name != receivedArray[1]) {
                                socket.send(sendData.str().c_str(), sendData.str().length(), client->ip, client->port);
                            }
                        }
                    }
                }

                else if(receivedArray[0] == "3") {
                    // seed response
                    // 3,{seed},
                    sendData.str(std::string());
                    sendData << "3," << serverSeed << ",";
                    socket.send(sendData.str().c_str(), sendData.str().length(), recvAddress, recvPort);
                }

            }

        }
    }

}
