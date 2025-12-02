#pragma once
#include "SpriteObject.h"
#include <iostream>

enum class PlayerDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    IDLE
};

// klasa gracza - dziedziczy po SpriteObject dla obsługi sprite'ów i animacji
class Player : public SpriteObject {
private:
    float speed;                    // prędkość ruchu gracza
    PlayerDirection currentDirection;  // aktualny kierunek ruchu
    PlayerDirection lastDirection;     // ostatni kierunek (dla animacji stania)
    
    // indeksy sprite'ów dla każdego kierunku
    size_t spriteIndexUp;
    size_t spriteIndexDown;
    size_t spriteIndexLeft;
    size_t spriteIndexRight;
    size_t spriteIndexIdle;

public:
    Player();
    virtual ~Player() = default;

    // wczytaj sprite'y dla wszystkich kierunków
    bool loadSprites(const std::string& spritesDir);

    // ustaw kierunek ruchu
    void setDirection(PlayerDirection direction);

    // pobierz aktualny kierunek
    PlayerDirection getDirection() const;

    // ustaw prędkość gracza
    void setSpeed(float newSpeed);

    // pobierz prędkość
    float getSpeed() const;

    // zaktualizuj pozycję gracza i animację (wirtualna metoda z AnimatedObject)
    virtual void animate(float deltaTime) override;

    // przesuń gracza w kierunku (dla obsługi klawiatury w pętli gry)
    void moveInDirection(PlayerDirection direction, float deltaTime);

    // zatrzymaj gracza (powrót do animacji IDLE)
    void stop();

    // informacje o graczu
    void printInfo() const;
};
