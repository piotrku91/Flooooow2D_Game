#include <SFML/Graphics.hpp>

extern sf::Window Window;

void winInit() {
    Window.create(sf::VideoMode(800, 600, 32), "5!");
    Window.setActive(true);
    Window.setKeyRepeatEnabled(true);
    Window.setFramerateLimit(60);
    Window.setPosition(sf::Vector2i(300, 30));
}