#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"

struct MapData{
    
    sf::Vector2i gridSize;

    std::vector<std::string> sBackgroundGrid;
    std::vector<std::string> sEntityGrid;
    std::vector<std::string> sEffectGrid;

    std::vector<std::vector<BackgroundTile>> backgroundGrid;
    std::vector<std::vector<EntityTile>> entityGrid;
    std::vector<std::vector<EffectTile>> effectGrid;

    int currentMap = 1;
    
} mapData;

struct PlayerData{
    
    sf::Vector2i playerPos = sf::Vector2i(1, 1);
    sf::Vector2i lastTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);
    sf::Vector2i currentTile = sf::Vector2i(14 + playerPos.x, 10 + playerPos.y);

} playerData;
