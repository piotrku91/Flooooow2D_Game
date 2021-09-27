#pragma once
#include <SFML/Graphics.hpp>
#include "TextureNet.hpp"
#include "Collid.h"

class rectRaw : public Collid {
private:


public:
   
    rectRaw(int posX, int posY, int sizeX, int sizeY, sf::Texture& texture) {
    Sprite_ = sf::Sprite(texture, sf::IntRect(0, 0, sizeX, sizeY));
   // Sprite_.setColor(sf::Color(0xffff00ff));
    Sprite_.setPosition(posX, posY);
    Sprite_.setOrigin(sf::Vector2f(0, 0));
    };

};

class Wall : public rectRaw
{
public:
Wall(int posX, int posY, int sizeX, int sizeY, sf::Texture& texture): rectRaw(posX, posY, sizeX, sizeY, texture) {};
};

class Ground : public rectRaw
{
public:
Ground(int posX, int posY, int sizeX, int sizeY, sf::Texture& texture): rectRaw(posX, posY, sizeX, sizeY, texture) {};
};

class Edge : public rectRaw
{
public:
Edge(int posX, int posY, int sizeX, int sizeY, sf::Texture& texture): rectRaw(posX, posY, sizeX, sizeY, texture) {};
};

class Platform {
private:
Wall wall_;
Ground ground_;
Edge edgeLeft_;
Edge edgeRight_;

public:
Wall& getWall() {return wall_;};
Edge& getEdge() {return edgeRight_;};
Ground& getGround() {return ground_;};
Platform(int posX, int posY, int sizeX, int sizeY, TextureNet TN):edgeLeft_(posX,posY,20,20,*TN.getTexture(0,3)), edgeRight_(posX+sizeX,posY,20,20,*TN.getTexture(0,3)), ground_(posX+20,posY,sizeX-20,20,*TN.getTexture(0,3)),wall_(posX+20,posY+20,sizeX-20,sizeY-20,*TN.getTexture(3,1)) {}


void goDraw(sf::RenderWindow& winHND)
{
    winHND.draw(wall_.getSprite());
    winHND.draw(ground_.getSprite());
    winHND.draw(edgeLeft_.getSprite());
    winHND.draw(edgeRight_.getSprite());

}
};