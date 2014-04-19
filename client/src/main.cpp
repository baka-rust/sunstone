#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "Player.h"
#include "Terrain.h"
#include "Network.h"

bool focused = true;

int main() {

    int scale = 4;
    int width = 256;
    int height = 160;

    sf::Event event;
    sf::Clock clock;
    float elapsedTime;

    sf::RenderWindow app(sf::VideoMode(width*scale, height*scale), "project sunstone", sf::Style::Titlebar | sf::Style::Close);
    sf::View camera(sf::FloatRect(0, 0, width, height));

    app.setVerticalSyncEnabled(true);
    app.setView(camera);

    Player player(64, 64, "down");
    Terrain terrain;
    Network network;

    player.terrain = &terrain;
    player.network = &network;
    network.terrain = &terrain;
    network.player = &player;

    while(app.isOpen()) {

        while(app.pollEvent(event)) {

            if(event.type == sf::Event::Closed) {
                app.close();
            }
            else if(event.type == sf::Event::GainedFocus) {
                focused = true;
                std::cout << "focus gained" << std::endl;
            }
            else if(event.type == sf::Event::LostFocus) {
                focused = false;
                std::cout << "focus lost" << std::endl;
            }


        }

        elapsedTime = clock.restart().asSeconds();

        terrain.update(elapsedTime);
        player.update(elapsedTime);
        network.update(elapsedTime);

        camera.setCenter(round(player.x * 10) / 10, round(player.y * 10) / 10);
        app.setView(camera);

        app.clear(sf::Color::Cyan);

        terrain.draw(camera.getCenter().x - 128, camera.getCenter().y - 80, &app);
        network.draw(&app);
        player.draw(&app);

        app.display();
    }

    return 0;
}
