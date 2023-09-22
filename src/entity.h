#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"

class Entity{

public:

    sf::RectangleShape rect;
    sf::Vector2i coords;

    bool exists = false;

    void setTexture(sf::Texture* texture);

    void setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords);

    void setWallUnder(Tile& tile);

    void unsetWallUnder(Tile& tile);

};

void::Entity::setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords){
    rect.setSize(size);
    rect.setPosition(position);
    this->coords = coords;
}

void::Entity::setTexture(sf::Texture* texture){
    rect.setTexture(texture);
}

void::Entity::setWallUnder(Tile& tile){
    tile.isWall = true;
}

void::Entity::unsetWallUnder(Tile& tile){
    tile.isWall = false;
}
