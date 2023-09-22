#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

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

template <size_t rows, size_t cols>
void setEntityMap(EntityTile (&entityGrid)[rows][cols], BackgroundTile (&backgroundGrid)[rows][cols], sf::Vector2i gridSize, std::string eMap[], sf::Texture* eTexture) {
    for(int i = 0; i < gridSize.x; i++){
        for(int j = 0; j < gridSize.y; j++){
            entityGrid[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(gridSize));
            if(eMap[j][i] == '1'){
                entityGrid[i][j].exists = true;
                entityGrid[i][j].setWallUnder(backgroundGrid[i][j]);
                entityGrid[i][j].setTexture(eTexture);
            }
        }
    }
}

template <size_t rows, size_t cols>
void drawGrid(BackgroundTile (&backgroundGrid)[rows][cols], EntityTile (&entityGrid)[rows][cols], sf::Vector2i gridSize, sf::RenderWindow& window, sf::Vector2i playerPos){
    for(int i = (playerPos.x - 8); i < (playerPos.x + 9); i++){
        for(int j = (playerPos.y - 6); j < (playerPos.y + 7); j++){

            if((i >= 0 && i < gridSize.x) && (j >= 0 && j < gridSize.y)){

                window.draw(backgroundGrid[i][j].rect); //pozadí

                if(entityGrid[i][j].exists){
                    window.draw(entityGrid[i][j].rect); //entita
                }

            }
        }
    }
}

template <size_t rows, size_t cols>
void overworldControlls(BackgroundTile (&backgroundGrid)[rows][cols], sf::Vector2i gridSize, sf::RenderWindow& window, bool& isThere, sf::Vector2i& currentTile, sf::Vector2i& lastTile, sf::Vector2i& playerPos, bool& sprint, sf::View& view){
    sf::Event event;
    if(isThere){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !backgroundGrid[currentTile.x - 14][currentTile.y - 11].isWall){
            currentTile.y--;
            playerPos.y--;
            isThere = 0;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !backgroundGrid[currentTile.x - 14][currentTile.y - 9].isWall){
            currentTile.y++;
            playerPos.y++;
            isThere = 0;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !backgroundGrid[currentTile.x - 15][currentTile.y - 10].isWall){
            currentTile.x--;
            playerPos.x--;
            isThere = 0;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !backgroundGrid[currentTile.x - 13][currentTile.y - 10].isWall){
            currentTile.x++;
            playerPos.x++;
            isThere = 0;

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            sprint = 1;
        }
        else{
            sprint = 0;
        }
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            std::cout << "x: " << currentTile.x - 14 << " y: " << currentTile.y - 10 << "\n";
        }

    }

    if(!isThere){
        if(sprint){
        view.move(sf::Vector2f( (currentTile.x < lastTile.x) ? -2 : ((currentTile.x > lastTile.x) ? 2 : 0), 
                                (currentTile.y < lastTile.y) ? -2 : ((currentTile.y > lastTile.y) ? 2 : 0)));
        }
        else{
        view.move(sf::Vector2f( (currentTile.x < lastTile.x) ? -1 : ((currentTile.x > lastTile.x) ? 1 : 0), 
                                (currentTile.y < lastTile.y) ? -1 : ((currentTile.y > lastTile.y) ? 1 : 0)));
        }
        int xC = view.getCenter().x;
        int yC = view.getCenter().y;

        if ((xC % 8 == 0 && xC % 16 != 0) && (yC % 8 == 0 && yC % 16 != 0)){
            isThere = 1;
            lastTile.x = currentTile.x;
            lastTile.y = currentTile.y;
        }
    }
}
