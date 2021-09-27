
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Platform.hpp"
#include "Player.hpp"
#include "TextureNet.hpp"

extern void winInit();

sf::RenderWindow Window;

std::map<std::string, TextureNet> TexturesDatabase =
    {
        {"ground", TextureNet("jeden.jpg", 200, 200, 800, 800)}};

int main() {
    /////////////////////////////////////////////////// WINDOW INIT ////////////////////////////////////////////
    winInit();
    int dX = 0, dY = 0;

    TextureNet bb("jeden.jpg", 200, 200, 800, 800);
    std::vector<Platform> Platforms;
    Platforms.emplace_back(100, 500, 400, 100, TexturesDatabase["ground"]);
    Platforms.emplace_back(480, 400, 400, 200, TexturesDatabase["ground"]);

    Player pl;
    pl.getSprite() = sf::Sprite(*TexturesDatabase["ground"].getTexture(1, 0), sf::IntRect(0, 0, 30, 30));
    pl.getSprite().setPosition(400, 400);
    pl.getSprite().setOrigin(sf::Vector2f(15, 0));

    sf::Event Event;
    float jumpLevel = 0;

    /////////////////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////
    while (Window.isOpen()) {
        dX = 0;

        pl.onGround = false;
        bool onR = false;
        bool onL = false;

        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            };
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dX = -5;
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dX = 5;
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (!pl.isJumping) && (!pl.onAir)) {
            dY = -30;
            pl.getSprite().move(sf::Vector2f(0, -1));
            jumpLevel = dY;
            pl.isJumping = true;
            pl.onAir = true;
        };

        for (auto& Platform : Platforms) {
            if (pl.testCollisionDown(Platform.getGround())) {
                pl.onGround = true;
                pl.isJumping = false;
                pl.onAir = false;
            }

            if (pl.testCollisionRight(Platform.getWall())) {
                onR = true;
                pl.isJumping = false;
            };

             if (pl.testCollisionRight(Platform.getGround())) {
                onR = true;
                pl.isJumping = false;
            };

             if (pl.testCollisionRight(Platform.getEdge())) {
                onR = true;
                pl.getSprite().move(sf::Vector2f(-20, 10));
            };

            if (pl.testCollisionLeft(Platform.getWall())) {
                onL = true;
                pl.isJumping = false;
            };
        }

        Window.clear();

        if ((pl.isJumping) && (!pl.onGround) && (!onL) && (!onR)) {
            if (jumpLevel < -150) {
                pl.isJumping = false;
            };
            pl.getSprite().move(sf::Vector2f(0, dY));
            jumpLevel += dY;
        };
        if ((dX > 0) && (!onR)) {
            pl.getSprite().move(sf::Vector2f(dX, 0));
        };
        if ((dX < 0) && (!onL)) {
            pl.getSprite().move(sf::Vector2f(dX, 0));
        };
        if ((!pl.onGround) && (!onL) && (!onR)) {
            pl.getSprite().move(sf::Vector2f(0, 5));
        };

        if ((onR) && (!pl.onGround))
        {
            pl.getSprite().move(sf::Vector2f(-8, -8));
        }; // Slide from Edge
        if ((onL) && (!pl.onGround))
        {
             pl.getSprite().move(sf::Vector2f(-8, 8));
        }; // Slide from Edge

        std::for_each(Platforms.begin(), Platforms.end(), [](auto& p) { p.goDraw(Window); });
        Window.draw(pl.getSprite());
        Window.display();
    }
}
