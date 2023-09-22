#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "entity.h"

template <size_t rows, size_t cols>
void setMap(Tile (&arr)[rows][cols], int numX, int numY, std::string sMap[], sf::Texture* grass, sf::Texture* barrier) {
    for(int i = 0; i < numX; i++){
        for(int j = 0; j < numY; j++){
            arr[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(numX, numY));
            if(sMap[j][i] == 'x'){
                arr[i][j].isWall = true;
                arr[i][j].setTexture(barrier);
            }
            else if(sMap[j][i] == 'g'){
                arr[i][j].setTexture(grass);
            }
            else{
                std::cout << i << ", " << j << "\n";
            }
        }
    }
}

template <size_t rows, size_t cols>
void setEMap(Entity (&arr)[rows][cols], Tile (&tArr)[rows][cols], int numX, int numY, std::string eMap[], sf::Texture* eTexture) {
    for(int i = 0; i < numX; i++){
        for(int j = 0; j < numY; j++){
            arr[i][j].setProps(sf::Vector2f(16, 16), sf::Vector2f(i * 16, j * 16), sf::Vector2i(numX, numY));
            if(eMap[j][i] == '1'){
                arr[i][j].exists = true;
                arr[i][j].setWallUnder(tArr[i][j]);
                arr[i][j].setTexture(eTexture);
            }
        }
    }
}

template <size_t rows, size_t cols>
void drawGrid(Tile (&arr)[rows][cols], Entity (&eArr)[rows][cols], int numX, int numY, sf::RenderWindow& window, sf::Vector2i playerPos){

    for(int i = (playerPos.x - 8); i < (playerPos.x + 9); i++){
        for(int j = (playerPos.y - 6); j < (playerPos.y + 7); j++){
            if((i >= 0 && i < numX) && (j >= 0 && j < numY)){
                window.draw(arr[i][j].rect);
                if(eArr[i][j].exists)
                    window.draw(eArr[i][j].rect);
            }
        }
    }
}

template <size_t rows, size_t cols>
void overworldControlls(Tile (&grid)[rows][cols], int numX, int numY, sf::RenderWindow& window, bool& isThere, sf::Vector2i& currentTile, sf::Vector2i& lastTile, sf::Vector2i& playerPos, bool& sprint, sf::View& view){
    sf::Event event;
    if(isThere){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !grid[currentTile.x - 14][currentTile.y - 11].isWall){
            currentTile.y--;
            playerPos.y--;
            isThere = 0;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !grid[currentTile.x - 14][currentTile.y - 9].isWall){
            currentTile.y++;
            playerPos.y++;
            isThere = 0;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !grid[currentTile.x - 15][currentTile.y - 10].isWall){
            currentTile.x--;
            playerPos.x--;
            isThere = 0;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !grid[currentTile.x - 13][currentTile.y - 10].isWall){
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
