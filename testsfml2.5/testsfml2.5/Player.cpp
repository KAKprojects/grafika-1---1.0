#include "Player.h"
#include <cmath>
#include <sstream>

Player::Player()
    : speed(150.0f),
      currentDirection(PlayerDirection::IDLE),
      lastDirection(PlayerDirection::DOWN),
      spriteIndexUp(0),
      spriteIndexDown(0),
      spriteIndexLeft(0),
      spriteIndexRight(0),
      spriteIndexIdle(0)
{
    std::cout << "[Player] Utworzono nowego gracza" << std::endl;
}

bool Player::loadSprites(const std::string& spritesDir)
{
    std::cout << "[Player] Wczytywanie sprite'ów z katalogu: " << spritesDir << std::endl;

    // próbujemy wczytać sprite'y dla każdego kierunku
    // jeśli sprite'y nie istnieją, tworzymy dummy sprite'y
    bool success = true;
    int loadedCount = 0;

    // kierunek UP (czerwony)
    std::string upPath = spritesDir + "/player_up_0.png";
    if (addBitmapFromFile(upPath)) {
        spriteIndexUp = getSpriteCount() - 1;
        std::cout << "[Player] UP załadowany" << std::endl;
        loadedCount++;
    } else {
        std::cout << "[Player] Nie znaleziono sprite'u UP, będzie używany placeholder" << std::endl;
        success = false;
    }

    // kierunek DOWN (zielony)
    std::string downPath = spritesDir + "/player_down_0.png";
    if (addBitmapFromFile(downPath)) {
        spriteIndexDown = getSpriteCount() - 1;
        std::cout << "[Player] DOWN załadowany" << std::endl;
        loadedCount++;
    } else {
        std::cout << "[Player] Nie znaleziono sprite'u DOWN, będzie używany placeholder" << std::endl;
        success = false;
    }

    // kierunek LEFT (niebieski)
    std::string leftPath = spritesDir + "/player_left_0.png";
    if (addBitmapFromFile(leftPath)) {
        spriteIndexLeft = getSpriteCount() - 1;
        std::cout << "[Player] LEFT załadowany" << std::endl;
        loadedCount++;
    } else {
        std::cout << "[Player] Nie znaleziono sprite'u LEFT, będzie używany placeholder" << std::endl;
        success = false;
    }

    // kierunek RIGHT (żółty)
    std::string rightPath = spritesDir + "/player_right_0.png";
    if (addBitmapFromFile(rightPath)) {
        spriteIndexRight = getSpriteCount() - 1;
        std::cout << "[Player] RIGHT załadowany" << std::endl;
        loadedCount++;
    } else {
        std::cout << "[Player] Nie znaleziono sprite'u RIGHT, będzie używany placeholder" << std::endl;
        success = false;
    }

    // kierunek IDLE (szary/neutralny) - jeśli dostępny, w innym razie używamy DOWN
    std::string idlePath = spritesDir + "/player_idle_0.png";
    if (addBitmapFromFile(idlePath)) {
        spriteIndexIdle = getSpriteCount() - 1;
        std::cout << "[Player] IDLE załadowany" << std::endl;
        loadedCount++;
    } else {
        // fallback: używamy sprite'u DOWN dla IDLE
        spriteIndexIdle = spriteIndexDown;
        std::cout << "[Player] IDLE nie znaleziony, używany sprite DOWN" << std::endl;
    }

    std::cout << "[Player] Załadowano " << loadedCount << " sprite'ów" << std::endl;

    // ustaw domyślny sprite
    if (getSpriteCount() > 0) {
        setCurrentSprite(spriteIndexDown);
        std::cout << "[Player] Ustawiono domyślny sprite" << std::endl;
    }

    // ustaw czas animacji
    setFrameDuration(0.1f);

    return success;
}

void Player::setDirection(PlayerDirection direction)
{
    if (currentDirection != direction) {
        currentDirection = direction;
        
        // zmień sprite w zależności od kierunku
        switch (direction) {
            case PlayerDirection::UP:
                setCurrentSprite(spriteIndexUp);
                std::cout << "[Player] Kierunek: UP" << std::endl;
                break;
            case PlayerDirection::DOWN:
                setCurrentSprite(spriteIndexDown);
                std::cout << "[Player] Kierunek: DOWN" << std::endl;
                break;
            case PlayerDirection::LEFT:
                setCurrentSprite(spriteIndexLeft);
                std::cout << "[Player] Kierunek: LEFT" << std::endl;
                break;
            case PlayerDirection::RIGHT:
                setCurrentSprite(spriteIndexRight);
                std::cout << "[Player] Kierunek: RIGHT" << std::endl;
                break;
            case PlayerDirection::IDLE:
                setCurrentSprite(spriteIndexIdle);
                std::cout << "[Player] Kierunek: IDLE" << std::endl;
                break;
        }
        lastDirection = direction;
    }
}

PlayerDirection Player::getDirection() const
{
    return currentDirection;
}

void Player::setSpeed(float newSpeed)
{
    if (newSpeed > 0.0f) {
        speed = newSpeed;
        std::cout << "[Player] Ustawiono prędkość: " << speed << " px/s" << std::endl;
    } else {
        std::cerr << "[Player] Błąd: prędkość musi być większa niż 0" << std::endl;
    }
}

float Player::getSpeed() const
{
    return speed;
}

void Player::animate(float deltaTime)
{
    // wywołaj animację sprite'ów z klasy SpriteObject
    SpriteObject::animate(deltaTime);
}

void Player::moveInDirection(PlayerDirection direction, float deltaTime)
{
    // ustaw kierunek
    setDirection(direction);

    // przesunięcie na podstawie kierunku i prędkości
    float distance = speed * deltaTime;
    float newX = getPosition().x;
    float newY = getPosition().y;

    switch (direction) {
        case PlayerDirection::UP:
            newY -= distance;
            break;
        case PlayerDirection::DOWN:
            newY += distance;
            break;
        case PlayerDirection::LEFT:
            newX -= distance;
            break;
        case PlayerDirection::RIGHT:
            newX += distance;
            break;
        case PlayerDirection::IDLE:
            // bez ruchu
            break;
    }

    setPosition(newX, newY);
}

void Player::stop()
{
    currentDirection = PlayerDirection::IDLE;
    setCurrentSprite(spriteIndexIdle);
    std::cout << "[Player] Zatrzymano" << std::endl;
}

void Player::printInfo() const
{
    std::cout << " --- INFORMACJE O GRACZU ---" << std::endl;
    std::cout << "Pozycja: (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
    std::cout << "Prędkość: " << speed << " px/s" << std::endl;
    
    std::string dirStr;
    switch (currentDirection) {
        case PlayerDirection::UP: dirStr = "UP"; break;
        case PlayerDirection::DOWN: dirStr = "DOWN"; break;
        case PlayerDirection::LEFT: dirStr = "LEFT"; break;
        case PlayerDirection::RIGHT: dirStr = "RIGHT"; break;
        case PlayerDirection::IDLE: dirStr = "IDLE"; break;
    }
    std::cout << "Kierunek: " << dirStr << std::endl;
    std::cout << "Aktualny sprite: " << getCurrentSpriteIndex() << " / " << (getSpriteCount() - 1) << std::endl;
    std::cout << "Czas klatki: " << getFrameDuration() << " s" << std::endl;
    std::cout << "Widoczność: " << (getVisible() ? "tak" : "nie") << std::endl;
    std::cout << " -------------------------" << std::endl;
}
