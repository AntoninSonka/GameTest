#pragma once

#include <SFML/Graphics.hpp>

class Tile {

private:


    sf::Vector2i coords;


public:

    sf::RectangleShape rect;

    bool isPlayerOn = false;

    void setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords, bool isWall);

    void setTexture(sf::Texture* texture);

    bool isWall = false;

};

void::Tile::setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords, bool isWall = false) {

    rect.setSize(size);
    rect.setPosition(position);
    this->coords = coords;
    this->isWall = isWall;

}

void::Tile::setTexture(sf::Texture* texture) {
    rect.setTexture(texture);
}
