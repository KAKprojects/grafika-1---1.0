#include "SpriteObject.h"
#include <iostream>

SpriteObject::SpriteObject()
    : currentSpriteIndex(0), animationTimer(0.0f), frameDuration(0.1f)
{
    // konstruktor
}

void SpriteObject::setCurrentSprite(size_t index)
{
    if (index < sprites.size()) {
        currentSpriteIndex = index;
        std::cout << "[SpriteObject] Zmieniono sprite na indeks: " << index << std::endl;
    } else {
        std::cerr << "[SpriteObject] Błąd: indeks sprite'u poza zakresem" << std::endl;
    }
}

size_t SpriteObject::getCurrentSpriteIndex() const
{
    return currentSpriteIndex;
}

void SpriteObject::setFrameDuration(float duration)
{
    if (duration > 0.0f) {
        frameDuration = duration;
        std::cout << "[SpriteObject] Ustalono czas klatki: " << duration << " sekund" << std::endl;
    } else {
        std::cerr << "[SpriteObject] Błąd: czas klatki musi być większy niż 0" << std::endl;
    }
}

float SpriteObject::getFrameDuration() const
{
    return frameDuration;
}

void SpriteObject::resetAnimationTimer()
{
    animationTimer = 0.0f;
}

void SpriteObject::animate(float deltaTime)
{
    if (sprites.empty()) {
        return;
    }

    // dodaj upłynięty czas do timera
    animationTimer += deltaTime;

    // jeśli czas превысił czas jednej klatki, przejdź do następnej
    if (animationTimer >= frameDuration) {
        animationTimer = 0.0f;
        currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
    }
}

void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!isVisible || sprites.empty()) {
        return;
    }

    // stosuj transformacje obiektu
    states.transform *= getTransform();

    // rysuj tylko aktualny sprite
    target.draw(sprites[currentSpriteIndex], states);
}
