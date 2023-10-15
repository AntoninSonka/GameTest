#pragma once

#include <SFML/Graphics.hpp>
#include "data.h"

sf::RectangleShape player;

sf::Texture* upTexture;
sf::Texture* downTexture;
sf::Texture* leftTexture;
sf::Texture* rightTexture;
sf::Texture* upWTexture;
sf::Texture* downWTexture;
sf::Texture* leftWTexture;
sf::Texture* rightWTexture;

int sprintCount = 0;
int normalCount = 0;

int realDirection = 0;

void setPlayerProps(sf::Texture* texture, sf::Texture* upTextu, sf::Texture* downTextu, sf::Texture* leftTextu, sf::Texture* rightTextu, sf::Texture* upWTextu, sf::Texture* downWTextu, sf::Texture* leftWTextu, sf::Texture* rightWTextu){
    player.setSize(sf::Vector2f(16, 16));
    player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
    player.setTexture(texture); //TODO dodělat víc textur a animace

    upTexture = upTextu;
    downTexture = downTextu;
    leftTexture = leftTextu;
    rightTexture = rightTextu;
    upWTexture = upWTextu;
    downWTexture = downWTextu;
    leftWTexture = leftWTextu;
    rightWTexture = rightWTextu;

}

void overworldControlls(sf::RenderWindow& window, bool& isThere, bool& sprint, sf::View& view){

    int direction = 0;

    if(isThere){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            direction = 1;
            realDirection = 1;
            if (!mapData.backgroundGrid[playerData.currentTile.x - 14][playerData.currentTile.y - 11].isWall){
                playerData.currentTile.y--;
                playerData.playerPos.y--;
                isThere = 0;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            direction = 2;
            realDirection = 2;
            if(!mapData.backgroundGrid[playerData.currentTile.x - 14][playerData.currentTile.y - 9].isWall){
                playerData.currentTile.y++;
                playerData.playerPos.y++;
                isThere = 0;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            direction = 3;
            realDirection = 3;
            if(!mapData.backgroundGrid[playerData.currentTile.x - 15][playerData.currentTile.y - 10].isWall){
                playerData.currentTile.x--;
                playerData.playerPos.x--;
                isThere = 0;
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            direction = 4;
            realDirection = 4;
            if(!mapData.backgroundGrid[playerData.currentTile.x - 13][playerData.currentTile.y - 10].isWall){
                playerData.currentTile.x++;
                playerData.playerPos.x++;
                isThere = 0;
            }
        }
        else {
            direction = 0;
        }
        
        if(player.getTexture() != upWTexture || player.getTexture() != downWTexture || player.getTexture() != leftWTexture || player.getTexture() != rightWTexture){
            if(direction == 1 && player.getTexture() != upTexture ){
                player.setTexture(upTexture);
            }
            else if(direction == 2 && player.getTexture() != downTexture ){
                player.setTexture(downTexture);
            }
            else if(direction == 3 && player.getTexture() != leftTexture ){
                player.setTexture(leftTexture);
            }
            else if(direction == 4 && player.getTexture() != rightTexture ){
                player.setTexture(rightTexture);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            sprint = 1;
        }
        else{
            sprint = 0;
        }
    }

    //samotný pohybování se a sprintování, pomocí hýbání view, dokavaď se tam kamera nedostane
    if(!isThere){
        if(sprint){
        view.move(sf::Vector2f( (playerData.currentTile.x < playerData.lastTile.x) ? -2 : ((playerData.currentTile.x > playerData.lastTile.x) ? 2 : 0), 
                                (playerData.currentTile.y < playerData.lastTile.y) ? -2 : ((playerData.currentTile.y > playerData.lastTile.y) ? 2 : 0)));
            sprintCount++;
        }
        else{
        view.move(sf::Vector2f( (playerData.currentTile.x < playerData.lastTile.x) ? -1 : ((playerData.currentTile.x > playerData.lastTile.x) ? 1 : 0), 
                                (playerData.currentTile.y < playerData.lastTile.y) ? -1 : ((playerData.currentTile.y > playerData.lastTile.y) ? 1 : 0)));
            normalCount++;
        }
        if((normalCount >= 4 && normalCount <= 12) || (sprintCount >= 2 && sprintCount <= 6)){
            if(realDirection == 1 && player.getTexture() != upWTexture ){
                player.setTexture(upWTexture);
            }
            else if(realDirection == 2 && player.getTexture() != downWTexture ){
                player.setTexture(downWTexture);
            }
            else if(realDirection == 3 && player.getTexture() != leftWTexture ){
                player.setTexture(leftWTexture);
            }
            else if(realDirection == 4 && player.getTexture() != rightWTexture ){
                player.setTexture(rightWTexture);
            }
        }
        else{
            if(realDirection == 1 && player.getTexture() != upTexture ){
                player.setTexture(upTexture);
            }
            else if(realDirection == 2 && player.getTexture() != downTexture ){
                player.setTexture(downTexture);
            }
            else if(realDirection == 3 && player.getTexture() != leftTexture ){
                player.setTexture(leftTexture);
            }
            else if(realDirection == 4 && player.getTexture() != rightTexture ){
                player.setTexture(rightTexture);
            }
        }
        int xC = view.getCenter().x;
        int yC = view.getCenter().y;

        if ((xC % 8 == 0 && xC % 16 != 0) && (yC % 8 == 0 && yC % 16 != 0)){ //pokod se tam dojde, tak se zastaví a lastTile je currentTile
            isThere = 1;
            playerData.lastTile.x = playerData.currentTile.x;
            playerData.lastTile.y = playerData.currentTile.y;
            sprintCount = 0;
            normalCount = 0;
        }
    }
}
