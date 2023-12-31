#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "tile.h"
#include "player.h"
#include "data.h"

//setování pozadí
void setBackgroundMap( sf::Texture* grass, sf::Texture* barrier) {

    for(int i = 0; i < mapData.gridSize.x; i++){
        for(int j = 0; j < mapData.gridSize.y; j++){
            mapData.backgroundGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(mapData.gridSize.x, mapData.gridSize.y));
            if(mapData.sBackgroundGrid[j][i] == 'x'){
                mapData.backgroundGrid[i][j].isWall = true;
                mapData.backgroundGrid[i][j].setTexture(barrier);
            }
            else if(mapData.sBackgroundGrid[j][i] == 'g'){
                mapData.backgroundGrid[i][j].setTexture(grass);
            }
            else{
                std::cout << i << ", " << j << "background failed\n";
            }
        }
    }
}

//setování entit
void setEntityMap(sf::Texture* eTexture) {

    for(int i = 0; i < mapData.gridSize.x; i++){
        for(int j = 0; j < mapData.gridSize.y; j++){
            if(mapData.sEntityGrid[j][i] == 'e'){
                mapData.entityGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(i, j));
                mapData.entityGrid[i][j].exists = true;
                mapData.entityGrid[i][j].setWallUnder(mapData.backgroundGrid[i][j]);
                mapData.entityGrid[i][j].setTexture(eTexture);
            }
        }
    }
}

//setování efektů
void setEffectMap(sf::Texture* fTexture) {

    for(int i = 0; i < mapData.gridSize.x; i++){
        for(int j = 0; j < mapData.gridSize.y; j++){
            if(mapData.sEffectGrid[j][i] == 's'){
                mapData.effectGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(i, j));
                mapData.effectGrid[i][j].exists = true;
                mapData.effectGrid[i][j].setTexture(fTexture);
            }
        }
    }
}

void drawGrid(sf::RenderWindow& window, sf::Vector2i lastTile, sf::View& view){

    for(int i = (playerData.playerPos.x - 8); i < (playerData.playerPos.x + 9); i++){
        for(int j = (playerData.playerPos.y - 6); j < (playerData.playerPos.y + 7); j++){

            if((i >= 0 && i < mapData.gridSize.x) && (j >= 0 && j < mapData.gridSize.y)){

                window.draw(mapData.backgroundGrid[i][j].rect); //pozadí

                if(mapData.entityGrid[i][j].exists){
                    window.draw(mapData.entityGrid[i][j].rect); //entita
                }

                if(mapData.effectGrid[i][j].exists && mapData.effectGrid[i][j].coords != playerData.playerPos && mapData.effectGrid[i][j].coords != lastTile){
                    window.draw(mapData.effectGrid[i][j].rect); //effect
                }
            }
        }
    }
    player.setPosition(view.getCenter());//tady se kreslí stíny přez hráče, což je currentTile a lastTile
    window.draw(player);
    window.draw(mapData.effectGrid[playerData.playerPos.x][playerData.playerPos.y].rect);
    if(lastTile != playerData.playerPos){
        window.draw(mapData.effectGrid[lastTile.x][lastTile.y].rect);
    }
}

int readMapFromText(std::string path){

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
    
    mapData.sBackgroundGrid.resize(ySize);
    int i = 3;
    while(text[i][0] != '_'){
        mapData.sBackgroundGrid[i - 3] = text[i];
        i++;
    }
    i++;
    while(text[i][0] != '_'){
        mapData.sEntityGrid[i - 4 - ySize] = text[i];
        i++;
    }
    i++;
    while(text[i][0] != '_'){
        mapData.sEffectGrid[i - 5 - ySize * 2] = text[i];
        i++;
    }


    inputStream.close();
    return 0;
}

void setupMap(int levelNum, sf::Texture texture[]){
    texture[0].loadFromFile("../textures/Grass.png");
    texture[1].loadFromFile("../textures/Barrier.png");
    texture[2].loadFromFile("../textures/Player.png");
    texture[3].loadFromFile("../textures/Entity.png");
    texture[4].loadFromFile("../textures/Shadow.png");
    texture[5].loadFromFile("../textures/PlayerUp.png");
    texture[6].loadFromFile("../textures/PlayerDown.png");
    texture[7].loadFromFile("../textures/PlayerLeft.png");
    texture[8].loadFromFile("../textures/PlayerRight.png");
    texture[9].loadFromFile("../textures/PlayerUpW.png");
    texture[10].loadFromFile("../textures/PlayerDownW.png");
    texture[11].loadFromFile("../textures/PlayerLeftW.png");
    texture[12].loadFromFile("../textures/PlayerRightW.png");
    switch(levelNum){
    case 1:
        mapData.gridSize = sf::Vector2i(50, 50);

        for(int i = 0; i < mapData.gridSize.y; i++){
            mapData.sBackgroundGrid.push_back("");
            mapData.sEntityGrid.push_back("");
            mapData.sEffectGrid.push_back("");
        }

        for(int i = 0; i < mapData.gridSize.x; i++){
            std::vector<BackgroundTile> underGrid;
            std::vector<EntityTile> underEGrid;
            std::vector<EffectTile> underFGrid;
            for(int j = 0; j < mapData.gridSize.y; j++){
                BackgroundTile bObj;
                EntityTile eObj;
                EffectTile fObj;

                underGrid.push_back(bObj);
                underEGrid.push_back(eObj);
                underFGrid.push_back(fObj);
            }
            mapData.backgroundGrid.push_back(underGrid);
            mapData.entityGrid.push_back(underEGrid);
            mapData.effectGrid.push_back(underFGrid);
        }

        readMapFromText("../maps/map1.txt");

        setBackgroundMap(&texture[0], &texture[1]);
        setEntityMap(&texture[3]);
        setEffectMap(&texture[4]);
        break;
    case 2:
        mapData.gridSize = sf::Vector2i(10, 9);

        for(int i = 0; i < mapData.gridSize.y; i++){
            mapData.sBackgroundGrid.push_back("");
            mapData.sEntityGrid.push_back("");
            mapData.sEffectGrid.push_back("");
        }

        for(int i = 0; i < mapData.gridSize.x; i++){
            std::vector<BackgroundTile> underGrid;
            std::vector<EntityTile> underEGrid;
            std::vector<EffectTile> underFGrid;
            for(int j = 0; j < mapData.gridSize.y; j++){
                BackgroundTile bObj;
                EntityTile eObj;
                EffectTile fObj;

                underGrid.push_back(bObj);
                underEGrid.push_back(eObj);
                underFGrid.push_back(fObj);
            }
            mapData.backgroundGrid.push_back(underGrid);
            mapData.entityGrid.push_back(underEGrid);
            mapData.effectGrid.push_back(underFGrid);
        }

        readMapFromText("../maps/map2.txt");

        setBackgroundMap(&texture[0], &texture[1]);
        setEntityMap(&texture[3]);
        setEffectMap(&texture[4]);
        break;
    case 3:
        mapData.gridSize = sf::Vector2i(25, 25);

        for(int i = 0; i < mapData.gridSize.y; i++){
            mapData.sBackgroundGrid.push_back("");
            mapData.sEntityGrid.push_back("");
            mapData.sEffectGrid.push_back("");
        }

        for(int i = 0; i < mapData.gridSize.x; i++){
            std::vector<BackgroundTile> underGrid;
            std::vector<EntityTile> underEGrid;
            std::vector<EffectTile> underFGrid;
            for(int j = 0; j < mapData.gridSize.y; j++){
                BackgroundTile bObj;
                EntityTile eObj;
                EffectTile fObj;

                underGrid.push_back(bObj);
                underEGrid.push_back(eObj);
                underFGrid.push_back(fObj);
            }
            mapData.backgroundGrid.push_back(underGrid);
            mapData.entityGrid.push_back(underEGrid);
            mapData.effectGrid.push_back(underFGrid);
        }

        readMapFromText("../maps/map3.txt");

        setBackgroundMap(&texture[0], &texture[1]);
        setEntityMap(&texture[3]);
        setEffectMap(&texture[4]);
        break;
    default:
        break;
    }
}

void changeMap(int whichMap, sf::Vector2i positionOfPlayer, sf::View& view, sf::Texture texture[]){

    mapData.backgroundGrid.clear();
    mapData.entityGrid.clear();
    mapData.effectGrid.clear();
    mapData.sBackgroundGrid.clear();
    mapData.sEntityGrid.clear();
    mapData.sEffectGrid.clear();
    playerData.playerPos = positionOfPlayer;
    playerData.lastTile = sf::Vector2i(14 + playerData.playerPos.x, 10 + playerData.playerPos.y);
    playerData.currentTile = sf::Vector2i(14 + playerData.playerPos.x, 10 + playerData.playerPos.y);
    view.setCenter(sf::Vector2f(playerData.playerPos.x * 16 + 8, playerData.playerPos.y * 16 + 8));
    setupMap(whichMap, texture);
}

