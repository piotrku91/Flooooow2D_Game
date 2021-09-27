
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



    std::vector<Platform> Platforms;
    Platforms.emplace_back(100, 500, 400, 100, TexturesDatabase["ground"]);
    Platforms.emplace_back(400, 300, 400, 300, TexturesDatabase["ground"]);

    std::vector<std::shared_ptr<Body>> Objects;
    Objects.push_back(std::make_shared<Player>(Player(*TexturesDatabase["ground"].getTexture(1, 0),400,400,30,30)));
    Objects.push_back(std::make_shared<Box>(Box(*TexturesDatabase["ground"].getTexture(1, 0),200,100,80,80)));
    //Player pl(*TexturesDatabase["ground"].getTexture(1, 0),400,400,30,30);
  //  Box box(*TexturesDatabase["ground"].getTexture(1, 3),200,100,80,80);;


    sf::Event Event;
  

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
            dY=-30;
        };

        
        auto checkCollisions = [&](){
            for (auto& Platform : Platforms) {
                for (auto& Object: Objects) {
            Object->PlatformCollisionTest(Platform);
                };
            };
        };

        checkCollisions(); // Check collisions for gravity and player moves


        Objects[1]->tryMove(0,0); // do Gravity
        Objects.front()->tryMove(dX,dY); // move player
 

       
        Objects[1]->Interaction(checkCollisions, *Objects[0]); // Check interactions
       
        
        
       
        
       
        Window.clear();
        std::for_each(Platforms.begin(), Platforms.end(), [](auto& p) { p.goDraw(Window); });
        for (auto& Object : Objects) {Window.draw(Object->getSprite());};
        Window.display();
    }
}
