#pragma once
#include "Body.hpp"


class Box : public Body {
public:
    Box(const sf::Texture& texture, float posX, float posY, float sizeX, float sizeY)
        : Body(texture, posX, posY, sizeX, sizeY){};

    virtual void tryMove(int dX, int dY);
    virtual void Interaction(std::function<void()> checkCollFunc, const std::shared_ptr<Body>& withObject);
    
};