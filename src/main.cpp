#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "overworld.h"
#include "tile.h"
#include "player.h"
#include "data.h"

int main(){

    const int IPS = 60; 

    std::chrono::milliseconds iDuration(1000 /  IPS);

    sf::RenderWindow window(sf::VideoMode(1024, 1024.f / 1.5f), "Game Test");

    /*sf::Texture texture[9];

    sf::Vector2i gridSize;

    std::vector<std::string> sGrid;
    std::vector<std::string> sEGrid;
    std::vector<std::string> sFGrid;

    std::vector<std::vector<BackgroundTile>> grid;
    std::vector<std::vector<EntityTile>> eGrid;
    std::vector<std::vector<EffectTile>> fGrid;

    int currentMap = 1;
    */
    sf::Texture texture[9];

    setupMap(mapData.currentMap, texture, mapData.gridSize, mapData.sBackgroundGrid, mapData.sEntityGrid, mapData.sEffectGrid, mapData.backgroundGrid, mapData.entityGrid, mapData.effectGrid);



    window.setFramerateLimit(60); 

    //sf::Vector2i playerPos = sf::Vector2i(1, 1);

    sf::View view(sf::Vector2f(playerData.playerPos.x * 16 + 8, playerData.playerPos.y * 16 + 8), sf::Vector2f(240.f, 240.f / 1.5f));


    //sf::Vector2i lastTile, currentTile;
    bool isThere = true;
    bool sprint = false;

    //lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    //currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);

    setPlayerProps(&texture[2], &texture[5], &texture[6], &texture[7], &texture[8]);
 

    while (window.isOpen())
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        //!-------------------------------------------------------

        overworldControlls(mapData.backgroundGrid, mapData.entityGrid, mapData.gridSize, window, isThere, playerData.currentTile, playerData.lastTile, playerData.playerPos, sprint, view);

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(mapData.entityGrid[2][2].isInRange(playerData.playerPos)){
                if(mapData.entityGrid[2][2].isTriggered(playerData.playerPos, realDirection)){
                    if(mapData.currentMap == 1){
                        changeMap(2, sf::Vector2i(1, 1), mapData.sBackgroundGrid, mapData.sEntityGrid, mapData.sEffectGrid, mapData.backgroundGrid, mapData.entityGrid, mapData.effectGrid, view, playerData.playerPos, playerData.lastTile, playerData.currentTile, mapData.gridSize, texture);
                        mapData.currentMap = 2;
                    }
                    else if(mapData.currentMap == 2){
                        changeMap(3, sf::Vector2i(1, 1), mapData.sBackgroundGrid, mapData.sEntityGrid, mapData.sEffectGrid, mapData.backgroundGrid, mapData.entityGrid, mapData.effectGrid, view, playerData.playerPos, playerData.lastTile, playerData.currentTile, mapData.gridSize, texture);
                        mapData.currentMap = 3;
                    }
                    else{
                        changeMap(1, sf::Vector2i(1, 1), mapData.sBackgroundGrid, mapData.sEntityGrid, mapData.sEffectGrid, mapData.backgroundGrid, mapData.entityGrid, mapData.effectGrid, view, playerData.playerPos, playerData.lastTile, playerData.currentTile, mapData.gridSize, texture);
                        mapData.currentMap = 1;

                    }
                }
            }
        }

        window.clear();
        window.setView(view);
        drawGrid(window, sf::Vector2i(playerData.lastTile.x - 14, playerData.lastTile.y - 10), view);
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
