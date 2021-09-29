
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Platform.hpp"
#include "Body.hpp"
#include "Player.hpp"
#include "Box.hpp"
#include "TextureNet.hpp"

extern void winInit();

sf::RenderWindow Window;

std::map<std::string, TextureNet> TexturesDatabase =
    {
        {"ground", TextureNet("jeden.jpg", 200, 200, 800, 800)}
    };

int main() {
    /////////////////////////////////////////////////// WINDOW INIT ////////////////////////////////////////////
    winInit();
    int dX = 0, dY = 0;

    std::vector<Platform> Platforms;
    Platforms.emplace_back(100, 500, 400, 100, TexturesDatabase["ground"]);
    Platforms.emplace_back(400, 300, 400, 300, TexturesDatabase["ground"]);

    std::shared_ptr<Body> Player_(std::make_shared<Player>(Player(*TexturesDatabase["ground"].getTexture(1, 0), 400, 400, 30, 30)));

    std::vector<std::shared_ptr<Body>> Objects;
    Objects.push_back(std::make_shared<Box>(Box(*TexturesDatabase["ground"].getTexture(1, 0), 260, 100, 50, 50)));
    Objects.push_back(std::make_shared<Box>(Box(*TexturesDatabase["ground"].getTexture(1, 0), 150, 100, 50, 50)));
    Objects.push_back(std::make_shared<Box>(Box(*TexturesDatabase["ground"].getTexture(1, 0), 450, 100, 50, 50)));
    Objects.push_back(std::make_shared<Box>(Box(*TexturesDatabase["ground"].getTexture(1, 0), 450, 2, 50, 50)));

    sf::Event Event;

          auto checkCollisions = [&]() { // Collision checker lambda expr
            for (auto& Platform : Platforms) {
                Player_->PlatformCollisionTest(Platform);
                for (auto& Object : Objects) {
                    Object->PlatformCollisionTest(Platform);
                };
            };
        };

    /////////////////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////
    while (Window.isOpen()) {
        dX = 0;
        dY = 0;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            dY = -30;
        };

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            Player_->Catch=true;
        } else { Player_->Catch=false;}

  

        checkCollisions();  // Check collisions for gravity and player moves

        for (auto& Object : Objects) {
            Object->tryMove(0, 0);
        };                         // do Gravity for all Objects loop

        Player_->tryMove(dX, dY);  // move player and gravity

        for (auto& Object : Objects) {
            Object->Interaction(checkCollisions, Player_);
            for (auto& ObjectX : Objects) {
            Object->Interaction(checkCollisions, ObjectX);
            }
        };  // Check interactions loop;

        Window.clear();
        std::for_each(Platforms.begin(), Platforms.end(), [](auto& p) { p.goDraw(Window); });
        for (auto& Object : Objects) {
            Window.draw(Object->getSprite());
        };
        Window.draw(Player_->getSprite());
        Window.display();
    }
}
