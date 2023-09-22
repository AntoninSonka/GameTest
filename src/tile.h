#pragma once

#include <SFML/Graphics.hpp>

class Tile {

public:

    sf::RectangleShape rect;
    sf::Vector2i coords;

    void setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords);
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

    bool isPlayerOn = false;
    bool isWall = false;

};



//!------------------------------------------
//? Entity classa

class EntityTile : public Tile {

public:

    bool exists = false;

    void setWallUnder(BackgroundTile& backgroundTile);
    void unsetWallUnder(BackgroundTile& backgroundTile);

};

void::EntityTile::setWallUnder(BackgroundTile& backgroundTile){
    backgroundTile.isWall = true;
}

void::EntityTile::unsetWallUnder(BackgroundTile& backgroundTile){
    backgroundTile.isWall = false;
}
