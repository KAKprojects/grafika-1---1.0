#pragma once
#include "BitmapObject.h"
#include "AnimatedObject.h"

// klasa dla obiektów gry renderowanych za pomocą bitmap i animowanych za pośrednictwem sprite'ów
// obsługuje animacje na podstawie klatek (sprite sheets)
class SpriteObject : public BitmapObject, public AnimatedObject {
protected:
    size_t currentSpriteIndex;              // indeks aktualnie wyświetlanego sprite'u
    float animationTimer;                   // timer dla animacji
    float frameDuration;                    // czas wyświetlania każdej klatki (w sekundach)

public:
    SpriteObject();
    virtual ~SpriteObject() = default;

    // ustaw aktualny sprite do wyświetlania
    void setCurrentSprite(size_t index);

    // pobierz indeks aktualnie wyświetlanego sprite'u
    size_t getCurrentSpriteIndex() const;

    // ustaw czas trwania każdej klatki animacji
    void setFrameDuration(float duration);

    // pobierz czas trwania klatki
    float getFrameDuration() const;

    // resetuj timer animacji
    void resetAnimationTimer();

    // wirtualna metoda animacji - zmienia bieżący sprite w zależności od czasu
    virtual void animate(float deltaTime) override;

    // wirtualna metoda rysowania - rysuje tylko aktualny sprite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
