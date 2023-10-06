#pragma once

#include <SFML/Graphics.hpp>

class Tile {

public:

    sf::RectangleShape rect;
    sf::Vector2i coords; //souřadnice políčka na gridu

    void setProps(sf::Vector2f size, sf::Vector2f position, sf::Vector2i coords); //není to constructor, protože pak by byl problém s arrayi
    void setTexture(sf::Texture* texture);

};

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

    bool isInRange(sf::Vector2i playerPos);

};

//!------------------------------------------
//? Effect classa

class EffectTile : public Tile {

public:

    bool exists = false;

};
