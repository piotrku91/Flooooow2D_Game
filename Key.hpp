#pragma once
#include "Body.hpp"

class Key : public Body {
public:
    Key(const sf::Texture& texture, float posX, float posY, float sizeX, float sizeY)
        : Body(texture, posX, posY, sizeX, sizeY){};
    virtual void Interaction(std::function<void()> checkCollFunc, Body& withObject){};
};