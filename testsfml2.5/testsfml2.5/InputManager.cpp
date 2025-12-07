#include "InputManager.h"

InputManager::InputManager(sf::Window& win)
    : kb(), ms(win)
{
}

void InputManager::update() {
    kb.update();
    ms.update();
}

Keyboard& InputManager::keyboard() { return kb; }
Mouse& InputManager::mouse() { return ms; }
