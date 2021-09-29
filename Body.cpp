#include <memory>
#include "Platform.hpp"
#include "Body.hpp"


Body::Body(const sf::Texture& texture, float posX, float posY, float sizeX, float sizeY)
    : isReset_(false), onGroundColl_(false), onRightColl_(false), onLeftColl_(false), onTopColl_(false), isJumping_(false), dY_(0), jumpLevel_(0) {
    Sprite_ = sf::Sprite(texture, sf::IntRect(0, 0, sizeX, sizeY));
    Sprite_.setPosition(posX, posY);
    Sprite_.setOrigin(sf::Vector2f(15, 0));
};

void Body::PlatformCollisionTest(Platform& Platform) {
    if (testCollisionDown(Platform.getGround())) {
        onGroundColl_ = true;
        isJumping_ = false;
    }

    if (testCollisionRight(Platform.getWall())) {
        onRightColl_ = true;
        isJumping_ = false;
    };

    if (testCollisionRight(Platform.getGround())) {
        onRightColl_ = true;
        isJumping_ = false;
    };

    if (testCollisionLeft(Platform.getGround())) {
        onLeftColl_ = true;
        isJumping_ = false;
    };

    if (testCollisionLeft(Platform.getWall())) {
        onLeftColl_ = true;
        isJumping_ = false;
    };
}

bool Body::ObjectCollisionTestRight(Collid& target) {
    if (testCollisionRight(target)) {
        onRightColl_ = true;
        isJumping_ = false;
        return true;
    };
    return false;
}

bool Body::ObjectCollisionTestLeft(Collid& target) {
    if (testCollisionLeft(target)) {
        onLeftColl_ = true;
        isJumping_ = false;
        return true;
    };
    return false;
}

bool Body::ObjectCollisionTest(Collid& target) {
    if (testCollision(target)) {
        return true;
    };
    return false;
}

bool Body::ObjectCollisionTestDown(Collid& target) {
    if (testCollisionDown(target)) {
        onGroundColl_ = true;
        isJumping_ = false;
        return true;
    };
    return false;
}

bool Body::ObjectCollisionTestTop(Collid& target) {
    if (testCollisionTop(target)) {
        onTopColl_ = true;
        isJumping_ = false;
        return true;
    };
    return false;
}

void Body::Jump(int dY) {
    if ((!isJumping_) && (onGroundColl_)) {
        dY_ = dY;
        getSprite().move(sf::Vector2f(0, -15));
        jumpLevel_ = dY_;

        isJumping_ = true;
        onGroundColl_ = false;
    };
}

void Body::tryMove(int dX, int dY) {
    dX_ = dX;
    // Jump support
    if (dY < 0) {
        Jump(dY);
    };
    if ((isJumping_) && (!onGroundColl_) && (!onLeftColl_) && (!onRightColl_)) {
        if (dY != 0) {
            dY_ = dY;
        }
        if (jumpLevel_ < -150) {
            isJumping_ = false;
        };
        Sprite_.move(sf::Vector2f(0, dY_));
        jumpLevel_ += dY_;
    };

    // Move to right support
    if ((dX > 0) && (!onRightColl_)) {
        getSprite().move(sf::Vector2f(dX, 0));
    };
    // Move to left support
    if ((dX < 0) && (!onLeftColl_)) {
        getSprite().move(sf::Vector2f(dX, 0));
    };

    // Gravity support
    if ((!onGroundColl_) && (!onLeftColl_) && (!onRightColl_)) {
        getSprite().move(sf::Vector2f(0, 5));
    };

    // Slide from Edge support
    if ((onRightColl_) && (!onGroundColl_)) {
        getSprite().move(sf::Vector2f(-18, -8));
        onRightColl_ = false;
        onGroundColl_ = false;
    };
    if ((onLeftColl_) && (!onGroundColl_)) {
        getSprite().move(sf::Vector2f(18, -8));
        onLeftColl_ = false;
        onGroundColl_ = false;
    };
    resetCollisions();
}

void Body::resetCollisions() {
    onGroundColl_ = false;
    onRightColl_ = false;
    onLeftColl_ = false;
    onTopColl_ = false;
}

 void Body::Interaction(std::function<void()> checkCollFunc, const std::shared_ptr<Body>& withObject){};