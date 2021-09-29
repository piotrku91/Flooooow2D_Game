#pragma once
#include "Body.hpp"

class Player : public Body {
public:
    Player(const sf::Texture& texture, float posX, float posY, float sizeX, float sizeY)
        : Body(texture, posX, posY, sizeX, sizeY){};
};