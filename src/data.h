#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"

struct MapData{
    
    sf::Vector2i gridSize;

    std::vector<std::string> sGrid;
    std::vector<std::string> sEGrid;
    std::vector<std::string> sFGrid;

    std::vector<std::vector<BackgroundTile>> grid;
    std::vector<std::vector<EntityTile>> eGrid;
    std::vector<std::vector<EffectTile>> fGrid;

    sf::Texture texture[9];

    int currentMap = 1;
    
} mapData;

struct PlayerData{
    
    sf::Vector2i playerPos = sf::Vector2i(1, 1);
    sf::Vector2i lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    sf::Vector2i currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);

} playerData;
