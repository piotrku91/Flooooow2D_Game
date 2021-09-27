#pragma once
#include <string>

class TextureNet {
private:
    sf::Image img_;
    int sizeX_;
    int sizeY_;
    int fullSizeX_;
    int fullSizeY_;
    std::vector<std::shared_ptr<sf::Texture>> tx_;
    int size_;

public:
     
    std::shared_ptr<sf::Texture> getTexture(int index) { return tx_.at(index); };
    std::shared_ptr<sf::Texture> getTexture(int rowIndex, int colIndex) { return tx_.at(rowIndex*getCols()+colIndex); };
    size_t getCols() const {return fullSizeX_/sizeX_;};
    size_t getRows() const {return fullSizeY_/sizeY_;};
    size_t size() const { return size_; };
    void reload(const std::string& fileName, int sizeX, int sizeY, int fullSizeX, int fullSizeY) {

        img_.loadFromFile(fileName);
        sizeX_=sizeX;
        sizeY_=sizeY;
        fullSizeX_=fullSizeX;
        fullSizeY_=fullSizeY;

        for (int actualPosY = 0; actualPosY <= fullSizeY - sizeY; actualPosY += sizeY) {
            for (int actualPosX = 0; actualPosX <= fullSizeX - sizeX; actualPosX += sizeX) {
                tx_.push_back(std::make_unique<sf::Texture>());
                tx_.back()->create(sizeX, sizeY);
                tx_.back()->loadFromImage(img_, sf::IntRect(actualPosX, actualPosY, sizeX, sizeY));
                tx_.back()->setRepeated(true);
                size_++;
            };
        };
    };

    TextureNet() {};
    TextureNet(const std::string& fileName, int sizeX, int sizeY, int fullSizeX, int fullSizeY):size_(0) {
        reload(fileName, sizeX, sizeY, fullSizeX, fullSizeY);
    };
};