#pragma once
#include <SFML/Window/Keyboard.hpp>

class Keyboard {
public:
    Keyboard();
    void update();
    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isWASDPressed(char c) const;
};
