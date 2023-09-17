#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "tile.h"
#include "overworld.h"
#include "player.h"

int main()
{

    const int IPS = 60;

    std::chrono::milliseconds iDuration(1000 /  IPS);

    sf::RenderWindow window(sf::VideoMode(1024, 1024.f / 1.5f), "Game Test");

    sf::Texture Grass, Barrier, pTexture;

    Grass.loadFromFile("../textures/Grass.png");
    Barrier.loadFromFile("../textures/Barrier.png");
    pTexture.loadFromFile("../textures/Player.png");

    std::string sGrid[50] = {
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xgggggggggggggxgxggggggggggggggggggggggggggggggggx",
        "xggggggggggggggxgggggggggggggggggggggggggggggggggx",
        "xgggggggggggggxxxggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xggggggggggggggggggggggggggggggggggggggggggggggggx",
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
    };

    Tile grid[50][50];

    setMap(grid, 50, 50, sGrid, &Grass, &Barrier);


    window.setFramerateLimit(60); 

    sf::Vector2i playerPos = sf::Vector2i(30, 30);

    sf::View view(sf::Vector2f(playerPos.x * 16 + 8, playerPos.y * 16 + 8), sf::Vector2f(240.f, 240.f / 1.5f));


    sf::Vector2i lastTile, currentTile;
    bool isThere = true;
    bool sprint = false;

    lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);

    Player p(&pTexture);
 

    while (window.isOpen())
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        //!-------------------------------------------------------

        overworldControlls(grid, 50, 50, window, isThere, currentTile, lastTile, playerPos, sprint, view);

        window.clear();
        window.setView(view);
        drawGrid(grid, 50, 50, window, playerPos);
        p.rect.setPosition(view.getCenter());
        window.draw(p.rect);
        window.display();

        //!-------------------------------------------------------

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        if(elapsedTime < iDuration){
            std::this_thread::sleep_for(iDuration - elapsedTime);
        }

    }

    return 0;
}