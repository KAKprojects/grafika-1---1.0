#include "Mouse.h"

Mouse::Mouse(sf::Window& win)
    : window(&win), pos(0,0)
{}

void Mouse::update() {
    if (window) pos = sf::Mouse::getPosition(*window);
}

sf::Vector2i Mouse::getPosition() const { return pos; }

bool Mouse::isButtonPressed(sf::Mouse::Button btn) const { return sf::Mouse::isButtonPressed(btn); }
