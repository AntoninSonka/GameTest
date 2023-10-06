#pragma once

#include <SFML/Graphics.hpp>

sf::RectangleShape player;

sf::Texture* upTexture;
sf::Texture* downTexture;
sf::Texture* leftTexture;
sf::Texture* rightTexture;

int realDirection = 0;

void setPlayerProps(sf::Texture* texture, sf::Texture* upTextu, sf::Texture* downTextu, sf::Texture* leftTextu, sf::Texture* rightTextu){
    player.setSize(sf::Vector2f(16, 16));
    player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
    player.setTexture(texture); //TODO dodělat víc textur a animace

    upTexture = upTextu;
    downTexture = downTextu;
    leftTexture = leftTextu;
    rightTexture = rightTextu;
}

void overworldControlls(std::vector<std::vector<BackgroundTile>>& backgroundGrid, std::vector<std::vector<EntityTile>>& entityGrid,
                        sf::Vector2i gridSize, sf::RenderWindow& window,
                        bool& isThere, sf::Vector2i& currentTile, sf::Vector2i& lastTile, sf::Vector2i& playerPos, bool& sprint, sf::View& view){

    sf::Event event;

    int direction = 0;

    if(isThere){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            direction = 1;
            realDirection = 1;
            if (!backgroundGrid[currentTile.x - 14][currentTile.y - 11].isWall){
                currentTile.y--;
                playerPos.y--;
                isThere = 0;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            direction = 2;
            realDirection = 2;
            if(!backgroundGrid[currentTile.x - 14][currentTile.y - 9].isWall){
                currentTile.y++;
                playerPos.y++;
                isThere = 0;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            direction = 3;
            realDirection = 3;
            if(!backgroundGrid[currentTile.x - 15][currentTile.y - 10].isWall){
                currentTile.x--;
                playerPos.x--;
                isThere = 0;
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            direction = 4;
            realDirection = 4;
            if(!backgroundGrid[currentTile.x - 13][currentTile.y - 10].isWall){
                currentTile.x++;
                playerPos.x++;
                isThere = 0;
            }
        }
        else {
            direction = 0;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(entityGrid[2][2].isInRange(playerPos)){
                if(entityGrid[2][2].isTriggered(playerPos, realDirection)){
                    std::cout << "neco\n";
                    std::cout << "x: " << currentTile.x - 14 << " y: " << currentTile.y - 10 << "\n";
                }
                else{
                    std::cout << "nic\n";
                    std::cout << "x: " << currentTile.x - 14 << " y: " << currentTile.y - 10 << "\n";
                }
            }
        }

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            sprint = 1;
        }
        else{
            sprint = 0;
        }
    }

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

    }


    //samotný pohybování se a sprintování, pomocí hýbání view, dokavaď se tam kamera nedostane
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

        if ((xC % 8 == 0 && xC % 16 != 0) && (yC % 8 == 0 && yC % 16 != 0)){ //pokod se tam dojde, tak se zastaví a lastTile je currentTile
            isThere = 1;
            lastTile.x = currentTile.x;
            lastTile.y = currentTile.y;
        }
    }
}
