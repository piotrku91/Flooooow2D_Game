#pragma once
#include <functional>
#include "Collid.h"

class Body : public Collid {
protected:
    bool isReset_;
    bool onGroundColl_;
    bool onRightColl_;
    bool onLeftColl_;
    bool onTopColl_;
    bool isJumping_;
    float jumpLevel_;
    float dY_;
    float dX_;
    

public:
    bool Catch = false; // temporary in public
    Body(const sf::Texture& texture, float posX, float posY, float sizeX, float sizeY);  //c-tor
    void PlatformCollisionTest(Platform& Platform);
    bool ObjectCollisionTestRight(Collid& target);
    bool ObjectCollisionTestLeft(Collid& target);
    bool ObjectCollisionTest(Collid& target);
    bool ObjectCollisionTestDown(Collid& target);
    bool ObjectCollisionTestTop(Collid& target);
    void Jump(int dY);
    void resetCollisions();
    virtual void tryMove(int dX, int dY);
    virtual void Interaction(std::function<void()> checkCollFunc, const std::shared_ptr<Body>& withObject);


// Getters
    float getLastDx() const {return dX_;};
    float getLastDy() const {return dY_;};
};




