#include <memory>
#include "Platform.hpp"
#include "Box.hpp"

void Box::tryMove(int dX, int dY) {
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
        if ((!onGroundColl_) && (!onLeftColl_) && (!onRightColl_) && (dX == 0) && (!onTopColl_)) {
            getSprite().move(sf::Vector2f(0, 5));
        };

        resetCollisions();
    }

 void Box::Interaction(std::function<void()> checkCollFunc, const std::shared_ptr<Body>& withObject) {
        if (withObject->Catch && (ObjectCollisionTestLeft(*withObject) || ObjectCollisionTestRight(*withObject))) {
            checkCollFunc();
            tryMove(withObject->getLastDx(), 0);
        }
        if (withObject->ObjectCollisionTestLeft(*this)) {
            checkCollFunc();
            tryMove(-5, 0);
        };
        if (withObject->ObjectCollisionTestRight(*this)) {
            checkCollFunc();
            tryMove(5, 0);
        };
        if (withObject->ObjectCollisionTestDown(*this)) {
            if (checkCollFunc(); ObjectCollisionTestTop(*withObject)) {
                checkCollFunc();
                tryMove(0, 0);
            }
        };
    };