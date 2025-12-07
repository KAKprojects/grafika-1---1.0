#include "Keyboard.h"

Keyboard::Keyboard() {}
void Keyboard::update() { /* nothing to cache for now */ }

bool Keyboard::isKeyPressed(sf::Keyboard::Key key) const {
    return sf::Keyboard::isKeyPressed(key);
}

bool Keyboard::isWASDPressed(char c) const {
    switch (c) {
        case 'W': case 'w': return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        case 'A': case 'a': return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        case 'S': case 's': return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        case 'D': case 'd': return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        default: return false;
    }
}
