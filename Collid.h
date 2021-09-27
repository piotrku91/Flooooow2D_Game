#pragma once
#include <SFML/Graphics.hpp>

class Collid {
protected:
    sf::Sprite Sprite_;

public:
 sf::Sprite& getSprite() {return Sprite_;};

protected:
    bool testCollision(Collid& target) {
  
        if  (Sprite_.getGlobalBounds().intersects(target.Sprite_.getGlobalBounds())) {return true;};
        return false;
    };

    bool testCollisionDown(Collid& target) {
        //  std::cout << "player " << ",l " << Sprite_.getGlobalBounds().left << ",t " << Sprite_.getGlobalBounds().top << ",w " << Sprite_.getGlobalBounds().width << ",h " << Sprite_.getGlobalBounds().height << "\n";
     //  std::cout << "object " << ",l " << target.Sprite_.getGlobalBounds().left << ",t " << target.Sprite_.getGlobalBounds().top << ",w " << target.Sprite_.getGlobalBounds().width << ",h " << target.Sprite_.getGlobalBounds().height << "\n"; 
  
        if  (Sprite_.getGlobalBounds().intersects(sf::FloatRect(target.Sprite_.getGlobalBounds().left,target.Sprite_.getGlobalBounds().top-2,target.Sprite_.getGlobalBounds().width,target.Sprite_.getGlobalBounds().height))) {
           std::cout << "kolizja\n";
           return true;};
        return false;
    };

    bool testCollisionTop(Collid& target) {
           if  (Sprite_.getGlobalBounds().intersects(sf::FloatRect(target.Sprite_.getGlobalBounds().left,target.Sprite_.getGlobalBounds().top,target.Sprite_.getGlobalBounds().width,target.Sprite_.getGlobalBounds().height))) {
      return true;};
      
        return false;
    };

    bool testCollisionLeft(Collid& target) {
    /*    std::cout << "player " << ",l " << Sprite_.getGlobalBounds().left << ",t " << Sprite_.getGlobalBounds().top << ",w " << Sprite_.getGlobalBounds().width << ",h " << Sprite_.getGlobalBounds().height << "\n";
       std::cout << "object " << ",l " << target.Sprite_.getGlobalBounds().left << ",t " << target.Sprite_.getGlobalBounds().top << ",w " << target.Sprite_.getGlobalBounds().width << ",h " << target.Sprite_.getGlobalBounds().height << "\n"; */
        if  (Sprite_.getGlobalBounds().intersects(sf::FloatRect(target.Sprite_.getGlobalBounds().left+15,target.Sprite_.getGlobalBounds().top+5,target.Sprite_.getGlobalBounds().width,target.Sprite_.getGlobalBounds().height))) {return true;};
        return false;
    };

    bool testCollisionRight(Collid& target) {
       
      if  (Sprite_.getGlobalBounds().intersects(sf::FloatRect(target.Sprite_.getGlobalBounds().left-15,target.Sprite_.getGlobalBounds().top+5,target.Sprite_.getGlobalBounds().width,target.Sprite_.getGlobalBounds().height))) {return true;};

        return false;
    };
};