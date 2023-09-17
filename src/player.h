#pragma once

#include <SFML/Graphics.hpp>

class Player{
private:

public:

    sf::RectangleShape rect;

    Player(sf::Texture* texture);

};

Player::Player(sf::Texture* texture){
    rect.setSize(sf::Vector2f(16, 16));
    rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
    rect.setTexture(texture); //TODO dodělat víc textur a animace
}