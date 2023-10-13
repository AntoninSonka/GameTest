#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "tile.h"
#include "player.h"

//setování pozadí
void setBackgroundMap(std::vector<std::vector<BackgroundTile>>& backgroundGrid, sf::Vector2i gridSize, 
                      std::vector<std::string>& sMap, sf::Texture* grass, sf::Texture* barrier) {

    for(int i = 0; i < gridSize.x; i++){
        for(int j = 0; j < gridSize.y; j++){
            backgroundGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(gridSize.x, gridSize.y));
            if(sMap[j][i] == 'x'){
                backgroundGrid[i][j].isWall = true;
                backgroundGrid[i][j].setTexture(barrier);
            }
            else if(sMap[j][i] == 'g'){
                backgroundGrid[i][j].setTexture(grass);
            }
            else{
                std::cout << i << ", " << j << "background failed\n";
            }
        }
    }
}

//setování entit
void setEntityMap(
                  std::vector<std::vector<EntityTile>>& entityGrid,
                  std::vector<std::vector<BackgroundTile>>& backgroundGrid, sf::Vector2i gridSize,
                  std::vector<std::string>& eMap, sf::Texture* eTexture) {

    for(int i = 0; i < gridSize.x; i++){
        for(int j = 0; j < gridSize.y; j++){
            if(eMap[j][i] == 'e'){
                entityGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(i, j));
                entityGrid[i][j].exists = true;
                entityGrid[i][j].setWallUnder(backgroundGrid[i][j]);
                entityGrid[i][j].setTexture(eTexture);
            }
        }
    }
}

//setování efektů
void setEffectMap(std::vector<std::vector<EffectTile>>& effectGrid, sf::Vector2i gridSize, 
                  std::vector<std::string>& fMap, sf::Texture* fTexture) {

    for(int i = 0; i < gridSize.x; i++){
        for(int j = 0; j < gridSize.y; j++){
            if(fMap[j][i] == 's'){
                effectGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(i, j));
                effectGrid[i][j].exists = true;
                effectGrid[i][j].setTexture(fTexture);
            }
        }
    }
}

void drawGrid(std::vector<std::vector<BackgroundTile>>& backgroundGrid,
              std::vector<std::vector<EntityTile>>& entityGrid,  
              std::vector<std::vector<EffectTile>>& effectGrid, sf::Vector2i gridSize, sf::RenderWindow& window, 
              sf::Vector2i playerPos, sf::Vector2i lastTile, sf::View& view){

    for(int i = (playerPos.x - 8); i < (playerPos.x + 9); i++){
        for(int j = (playerPos.y - 6); j < (playerPos.y + 7); j++){

            if((i >= 0 && i < gridSize.x) && (j >= 0 && j < gridSize.y)){

                window.draw(backgroundGrid[i][j].rect); //pozadí

                if(entityGrid[i][j].exists){
                    window.draw(entityGrid[i][j].rect); //entita
                }

                if(effectGrid[i][j].exists && effectGrid[i][j].coords != playerPos && effectGrid[i][j].coords != lastTile){
                    window.draw(effectGrid[i][j].rect); //effect
                }
            }
        }
    }
    player.setPosition(view.getCenter());//tady se kreslí stíny přez hráče, což je currentTile a lastTile
    window.draw(player);
    window.draw(effectGrid[playerPos.x][playerPos.y].rect);
    if(lastTile != playerPos){
        window.draw(effectGrid[lastTile.x][lastTile.y].rect);
    }
}

int readMapFromText(
                    std::vector<std::string>& backgroundMap,
                    std::vector<std::string>& entityMap, 
                    std::vector<std::string>& effectMap, std::string path){

    std::ifstream inputStream(path);

    if(!inputStream){
        std::cerr << "unable to open " << path << "\n";
        inputStream.close();
        return 1;
    }

    std::vector<std::string> text;

    std::string line;

    while(std::getline(inputStream, line)){
        text.push_back(line);
    }

    int xSize = std::stoi(text[0]);
    int ySize = std::stoi(text[1]);
    
    backgroundMap[ySize];
    int i = 3;
    while(text[i][0] != '_'){
        backgroundMap[i - 3] = text[i];
        i++;
    }
    i++;
    while(text[i][0] != '_'){
        entityMap[i - 4 - ySize] = text[i];
        i++;
    }
    i++;
    while(text[i][0] != '_'){
        effectMap[i - 5 - ySize * 2] = text[i];
        i++;
    }


    inputStream.close();
    return 0;
}

void setupMap(int levelNum, sf::Texture texture[], sf::Vector2i& gridSize, std::vector<std::string>& sGrid, std::vector<std::string>& sEGrid, std::vector<std::string>& sFGrid, std::vector<std::vector<BackgroundTile>>& grid, std::vector<std::vector<EntityTile>>& eGrid, std::vector<std::vector<EffectTile>>& fGrid){
    switch(levelNum){
    case 1:
        gridSize = sf::Vector2i(50, 50);
        
        texture[0].loadFromFile("../textures/Grass.png");
        texture[1].loadFromFile("../textures/Barrier.png");
        texture[2].loadFromFile("../textures/Player.png");
        texture[3].loadFromFile("../textures/Entity.png");
        texture[4].loadFromFile("../textures/Shadow.png");
        texture[5].loadFromFile("../textures/PlayerUp.png");
        texture[6].loadFromFile("../textures/PlayerDown.png");
        texture[7].loadFromFile("../textures/PlayerLeft.png");
        texture[8].loadFromFile("../textures/PlayerRight.png");

        for(int i = 0; i < gridSize.y; i++){
            sGrid.push_back("");
            sEGrid.push_back("");
            sFGrid.push_back("");
        }

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

        setBackgroundMap(grid, gridSize, sGrid, &texture[0], &texture[1]);
        setEntityMap(eGrid, grid, gridSize, sEGrid, &texture[3]);
        setEffectMap(fGrid, gridSize, sFGrid, &texture[4]);
        break;
    case 2:
        gridSize = sf::Vector2i(10, 9);

        texture[0].loadFromFile("../textures/Grass.png");
        texture[1].loadFromFile("../textures/Barrier.png");
        texture[2].loadFromFile("../textures/Player.png");
        texture[3].loadFromFile("../textures/Entity.png");
        texture[4].loadFromFile("../textures/Shadow.png");
        texture[5].loadFromFile("../textures/PlayerUp.png");
        texture[6].loadFromFile("../textures/PlayerDown.png");
        texture[7].loadFromFile("../textures/PlayerLeft.png");
        texture[8].loadFromFile("../textures/PlayerRight.png");

        for(int i = 0; i < gridSize.y; i++){
            sGrid.push_back("");
            sEGrid.push_back("");
            sFGrid.push_back("");
        }

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

        readMapFromText(sGrid, sEGrid, sFGrid, "../maps/map2.txt");

        setBackgroundMap(grid, gridSize, sGrid, &texture[0], &texture[1]);
        setEntityMap(eGrid, grid, gridSize, sEGrid, &texture[3]);
        setEffectMap(fGrid, gridSize, sFGrid, &texture[4]);
        break;
    case 3:
        gridSize = sf::Vector2i(25, 25);

        texture[0].loadFromFile("../textures/Grass.png");
        texture[1].loadFromFile("../textures/Barrier.png");
        texture[2].loadFromFile("../textures/Player.png");
        texture[3].loadFromFile("../textures/Entity.png");
        texture[4].loadFromFile("../textures/Shadow.png");
        texture[5].loadFromFile("../textures/PlayerUp.png");
        texture[6].loadFromFile("../textures/PlayerDown.png");
        texture[7].loadFromFile("../textures/PlayerLeft.png");
        texture[8].loadFromFile("../textures/PlayerRight.png");

        for(int i = 0; i < gridSize.y; i++){
            sGrid.push_back("");
            sEGrid.push_back("");
            sFGrid.push_back("");
        }

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

        readMapFromText(sGrid, sEGrid, sFGrid, "../maps/map3.txt");

        setBackgroundMap(grid, gridSize, sGrid, &texture[0], &texture[1]);
        setEntityMap(eGrid, grid, gridSize, sEGrid, &texture[3]);
        setEffectMap(fGrid, gridSize, sFGrid, &texture[4]);
        break;
    default:
        break;
    }
}

void changeMap(int whichMap,
               sf::Vector2i positionOfPlayer,
               std::vector<std::string>& sGrid,
               std::vector<std::string>& sEGrid, 
               std::vector<std::string>& sFGrid,
               std::vector<std::vector<BackgroundTile>>& grid,
               std::vector<std::vector<EntityTile>>& eGrid,
               std::vector<std::vector<EffectTile>>& fGrid,
               sf::View& view,
               sf::Vector2i& playerPos,
               sf::Vector2i& lastTile,
               sf::Vector2i& currentTile,
               sf::Vector2i& gridSize,
               sf::Texture texture[]){

    grid.clear();
    eGrid.clear();
    fGrid.clear();
    sGrid.clear();
    sEGrid.clear();
    sFGrid.clear();
    playerPos = positionOfPlayer;
    lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    view.setCenter(sf::Vector2f(playerPos.x * 16 + 8, playerPos.y * 16 + 8));
    setupMap(whichMap, texture, gridSize, sGrid, sEGrid, sFGrid, grid, eGrid, fGrid);
}

