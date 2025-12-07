#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include <SFML/Window.hpp>

class InputManager {
public:
    InputManager(sf::Window& win);
    void update();
    Keyboard& keyboard();
    Mouse& mouse();

private:
    Keyboard kb;
    Mouse ms;
};
