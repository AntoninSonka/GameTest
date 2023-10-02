#pragma once

#include <SFML/Graphics.hpp>

class Tile {

public:

    sf::RectangleShape rect;
    sf::Vector2i coords; //souřadnice políčka na gridu

    void setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords); //není to constructor, protože pak by byl problém s arrayi
    void setTexture(sf::Texture* texture);

};

void::Tile::setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords) {
    rect.setSize(size);
    rect.setPosition(position);
    this->coords = coords;
}

void::Tile::setTexture(sf::Texture* texture) {
    rect.setTexture(texture);
}



//!------------------------------------------
//? Background classa

class BackgroundTile : public Tile { //classa pro backgrount tiles

public:

    bool isPlayerOn = false; //!dosud nepoužitý, má význam později kvůli dveřím atd, možná předělám do entit
    bool isWall = false;

};



//!------------------------------------------
//? Entity classa

class EntityTile : public Tile {

public:

    bool exists = false; //je to kvůli generaci, aby se negenerovali zbytečný nepoužitý "sf::RectangleShape"

    void setWallUnder(BackgroundTile& backgroundTile);
    void unsetWallUnder(BackgroundTile& backgroundTile); //!    unsetne průchodnost i když byla nastavena na BackgrountTile 
                                                         //TODO modifikovat aby se to nestávalo
    bool isTriggered(sf::Vector2i playerPos, int direction);

};

void::EntityTile::setWallUnder(BackgroundTile& backgroundTile){
    backgroundTile.isWall = true;
}

void::EntityTile::unsetWallUnder(BackgroundTile& backgroundTile){
    backgroundTile.isWall = false;
}

bool::EntityTile::isTriggered(sf::Vector2i playerPos, int direction){
    switch(direction){
    case 1:
        if(playerPos.x == coords.x && (playerPos.y - 1) == coords.y){
            return 1;
        }
        break;

    case 2:
        if(playerPos.x == coords.x && (playerPos.y + 1) == coords.y){
            return 1;
        }
        break;

    case 3:
        if((playerPos.x - 1) == coords.x && playerPos.y == coords.y){
            return 1;
        }
        break;

    case 4:
        if((playerPos.x + 1) == coords.x && playerPos.y == coords.y){
            return 1;
        }
        break;

    default:
        break;
    };
    return 0;
}



//!------------------------------------------
//? Effect classa

class EffectTile : public Tile {

public:

    bool exists = false;

};
