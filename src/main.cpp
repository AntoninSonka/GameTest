#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "overworld.h"
#include "tile.h"
#include "player.h"

int main()
{

    const int IPS = 60; //fps defakto

    std::chrono::milliseconds iDuration(1000 /  IPS);

    sf::RenderWindow window(sf::VideoMode(1024, 1024.f / 1.5f), "Game Test");

    sf::Texture Grass, Barrier, pTexture, eTexture, fTexture;

    Grass.loadFromFile("../textures/Grass.png");
    Barrier.loadFromFile("../textures/Barrier.png");
    pTexture.loadFromFile("../textures/Player.png");
    eTexture.loadFromFile("../textures/Entity.png");
    fTexture.loadFromFile("../textures/Shadow.png");

    std::string sFGrid[50] = {
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                   sss                            ",
        "                   sss                            ",
        "                   ssssss                         ",
        "                     s ss                         ",
        "                     ssss                         ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  "
    };

    std::string sEGrid[50] = {
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                       111111                     ",
        "                       1    1                     ",
        "                       1 1111                     ",
        "                       1 1                        ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  "
    };

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

    BackgroundTile grid[50][50];
    EntityTile eGrid[50][50];
    EffectTile fGrid[50][50];

    sf::Vector2i gridSize = sf::Vector2i(50, 50);

    setBackgroundMap(grid, gridSize, sGrid, &Grass, &Barrier);
    setEntityMap(eGrid, grid, gridSize, sEGrid, &eTexture);
    setEffectMap(fGrid, gridSize, sFGrid, &fTexture);


    window.setFramerateLimit(60); 

    sf::Vector2i playerPos = sf::Vector2i(30, 30);

    sf::View view(sf::Vector2f(playerPos.x * 16 + 8, playerPos.y * 16 + 8), sf::Vector2f(240.f, 240.f / 1.5f));


    sf::Vector2i lastTile, currentTile;
    bool isThere = true;
    bool sprint = false;

    lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);

    setPlayerProps(&pTexture);
 

    while (window.isOpen())
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        //!-------------------------------------------------------

        overworldControlls(grid, gridSize, window, isThere, currentTile, lastTile, playerPos, sprint, view);

        window.clear();
        window.setView(view);
        drawGrid(grid, eGrid, fGrid, gridSize, window, playerPos, sf::Vector2i(lastTile.x - 14, lastTile.y - 10), view);
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
