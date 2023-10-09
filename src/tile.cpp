#include "tile.h"

void Tile::setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords) {
    rect.setSize(size);
    rect.setPosition(position);
    this->coords = coords;
}

void Tile::setTexture(sf::Texture* texture) {
    rect.setTexture(texture);
}

//Entity

void EntityTile::setWallUnder(BackgroundTile& backgroundTile){
    backgroundTile.isWall = true;
}

void EntityTile::unsetWallUnder(BackgroundTile& backgroundTile){
    backgroundTile.isWall = false;
}

bool EntityTile::isTriggered(sf::Vector2i playerPos, int direction){
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

bool EntityTile::isInRange(sf::Vector2i playerPos){
    if (!(coords.x > (playerPos.x - 2) && coords.x < (playerPos.x + 2)))
        return 0;

    if(!(coords.y > (playerPos.y - 2) && coords.y < (playerPos.y + 2)))
        return 0;

    return 1;
}
