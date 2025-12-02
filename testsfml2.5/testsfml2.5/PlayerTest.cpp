#include <iostream>
#include "Player.h"

int main()
{
    std::cout << "=== Test klasy Player ===" << std::endl;

    // test 1: utworzenie gracza
    std::cout << "\n[Test 1] Utworzenie gracza" << std::endl;
    Player player;
    player.setPosition(400.0f, 300.0f);
    player.setSpeed(200.0f);
    player.printInfo();

    // test 2: wczytywanie sprite'ów (pomijamy dla testu bez grafiki)
    std::cout << "\n[Test 2] Wczytywanie sprite'ów (omińięte - bez DISPLAY)" << std::endl;
    std::cout << "[Test] W pełnej aplikacji sprite'y będą wczytane za pomocą loadSprites()" << std::endl;

    // test 3: zmiana kierunku
    std::cout << "\n[Test 3] Zmiana kierunku ruchu" << std::endl;
    player.setDirection(PlayerDirection::UP);
    std::cout << "Aktualny kierunek: " << static_cast<int>(player.getDirection()) << std::endl;

    player.setDirection(PlayerDirection::DOWN);
    std::cout << "Aktualny kierunek: " << static_cast<int>(player.getDirection()) << std::endl;

    player.setDirection(PlayerDirection::LEFT);
    std::cout << "Aktualny kierunek: " << static_cast<int>(player.getDirection()) << std::endl;

    player.setDirection(PlayerDirection::RIGHT);
    std::cout << "Aktualny kierunek: " << static_cast<int>(player.getDirection()) << std::endl;

    // test 4: ruch i animacja
    std::cout << "\n[Test 4] Ruch gracza" << std::endl;
    player.setDirection(PlayerDirection::RIGHT);
    
    for (int i = 0; i < 5; ++i) {
        player.moveInDirection(PlayerDirection::RIGHT, 0.016f);  // ~60 FPS
        player.animate(0.016f);
        std::cout << "  Krok " << i << ": pozycja (" 
                  << player.getPosition().x << ", " 
                  << player.getPosition().y << "), sprite: " 
                  << player.getCurrentSpriteIndex() << std::endl;
    }

    // test 5: zatrzymanie
    std::cout << "\n[Test 5] Zatrzymanie gracza" << std::endl;
    player.stop();
    player.printInfo();

    // test 6: transformacje
    std::cout << "\n[Test 6] Transformacje" << std::endl;
    player.setScale(1.5f, 1.5f);
    player.setRotation(45.0f);
    std::cout << "Skala: (1.5, 1.5)" << std::endl;
    std::cout << "Rotacja: 45 stopni" << std::endl;

    // test 7: widoczność
    std::cout << "\n[Test 7] Widoczność" << std::endl;
    player.setVisible(false);
    std::cout << "Widoczność: " << (player.getVisible() ? "widoczny" : "niewidoczny") << std::endl;
    player.setVisible(true);
    std::cout << "Widoczność: " << (player.getVisible() ? "widoczny" : "niewidoczny") << std::endl;

    std::cout << "\n=== Koniec testów ===" << std::endl;
    return 0;
}
