#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "overworld.h"
#include "tile.h"
#include "player.h"

int main()
{

    const int IPS = 60; 

    std::chrono::milliseconds iDuration(1000 /  IPS);

    sf::RenderWindow window(sf::VideoMode(1024, 1024.f / 1.5f), "Game Test");

    sf::Texture Grass, Barrier, pTexture, eTexture, fTexture, upTexture, downTexture, leftTexture, rightTexture;

    Grass.loadFromFile("../textures/Grass.png");
    Barrier.loadFromFile("../textures/Barrier.png");
    pTexture.loadFromFile("../textures/Player.png");
    eTexture.loadFromFile("../textures/Entity.png");
    fTexture.loadFromFile("../textures/Shadow.png");
    upTexture.loadFromFile("../textures/PlayerUp.png");
    downTexture.loadFromFile("../textures/PlayerDown.png");
    leftTexture.loadFromFile("../textures/PlayerLeft.png");
    rightTexture.loadFromFile("../textures/PlayerRight.png");

    sf::Vector2i gridSize = sf::Vector2i(50, 50);

    std::vector<std::string> sGrid;
    std::vector<std::string> sEGrid;
    std::vector<std::string> sFGrid;

    for(int i = 0; i < gridSize.y; i++){
        sGrid.push_back("");
        sEGrid.push_back("");
        sFGrid.push_back("");
    }

    std::vector<std::vector<BackgroundTile>> grid;
    std::vector<std::vector<EntityTile>> eGrid;
    std::vector<std::vector<EffectTile>> fGrid;

    for(int i = 0; i < gridSize.x; i++){
        std::vector<BackgroundTile> underGrid;
        std::vector<EntityTile> underEGrid;
        std::vector<EffectTile> underFGrid;
        for(int j = 0; j < gridSize.y; j++){
            BackgroundTile bObj;
            EntityTile eObj;
            EffectTile fObj;

            underGrid.push_back(bObj);
            underEGrid.push_back(eObj);
            underFGrid.push_back(fObj);
        }
        grid.push_back(underGrid);
        eGrid.push_back(underEGrid);
        fGrid.push_back(underFGrid);
    }

    readMapFromText(sGrid, sEGrid, sFGrid, "../maps/map1.txt");

    setBackgroundMap(grid, gridSize, sGrid, &Grass, &Barrier);
    setEntityMap(eGrid, grid, gridSize, sEGrid, &eTexture);
    setEffectMap(fGrid, gridSize, sFGrid, &fTexture);


    window.setFramerateLimit(60); 

    sf::Vector2i playerPos = sf::Vector2i(1, 1);

    sf::View view(sf::Vector2f(playerPos.x * 16 + 8, playerPos.y * 16 + 8), sf::Vector2f(240.f, 240.f / 1.5f));


    sf::Vector2i lastTile, currentTile;
    bool isThere = true;
    bool sprint = false;

    lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);

    setPlayerProps(&pTexture, &upTexture, &downTexture, &leftTexture, &rightTexture);
 

    while (window.isOpen())
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        //!-------------------------------------------------------

        overworldControlls(grid, eGrid, gridSize, window, isThere, currentTile, lastTile, playerPos, sprint, view);

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
