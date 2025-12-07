#pragma once
#include <SFML/Window.hpp>

class Mouse {
public:
    Mouse(sf::Window& win);
    void update();
    sf::Vector2i getPosition() const;
    bool isButtonPressed(sf::Mouse::Button btn) const;

private:
    sf::Window* window;
    sf::Vector2i pos;
};
