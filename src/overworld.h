#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "player.h"

//setování pozadí
template <size_t rows, size_t cols>
void setBackgroundMap(BackgroundTile (&backgroundGrid)[rows][cols], sf::Vector2i gridSize, std::string sMap[], sf::Texture* grass, sf::Texture* barrier) {
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
template <size_t rows, size_t cols>
void setEntityMap(EntityTile (&entityGrid)[rows][cols], BackgroundTile (&backgroundGrid)[rows][cols], sf::Vector2i gridSize, std::string eMap[], sf::Texture* eTexture) {
    for(int i = 0; i < gridSize.x; i++){
        for(int j = 0; j < gridSize.y; j++){
            if(eMap[j][i] == '1'){
                entityGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(gridSize));
                entityGrid[i][j].exists = true;
                entityGrid[i][j].setWallUnder(backgroundGrid[i][j]);
                entityGrid[i][j].setTexture(eTexture);
            }
        }
    }
}

//setování efektů
template <size_t rows, size_t cols>
void setEffectMap(EffectTile (&effectGrid)[rows][cols], sf::Vector2i gridSize, std::string fMap[], sf::Texture* fTexture) {
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

template <size_t rows, size_t cols>
void drawGrid(BackgroundTile (&backgroundGrid)[rows][cols], EntityTile (&entityGrid)[rows][cols], EffectTile (&effectGrid)[rows][cols], sf::Vector2i gridSize, sf::RenderWindow& window, sf::Vector2i playerPos, sf::Vector2i lastTile, sf::View& view){
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
