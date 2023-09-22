#pragma once

#include <SFML/Graphics.hpp>

sf::RectangleShape player;

void setPlayerProps(sf::Texture* texture){
    player.setSize(sf::Vector2f(16, 16));
    player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
    player.setTexture(texture); //TODO dodělat víc textur a animace
}

