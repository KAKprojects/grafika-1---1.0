#include <iostream>
#include "BitmapObject.h"
#include "SpriteObject.h"
#include "AnimatedObject.h"

// prosty test hierarchii klas - bez interfejsu SFML
int main()
{
    std::cout << "=== Test hierarchii AnimatedObject, BitmapObject, SpriteObject ===" << std::endl;

    // test 1: AnimatedObject (interfejs abstrakcyjny)
    std::cout << "\n[Test 1] AnimatedObject - interfejs abstrakcyjny" << std::endl;
    std::cout << "  AnimatedObject posiada wirtualną metodę animate(float deltaTime)" << std::endl;
    std::cout << "  Nie można utworzyć instancji AnimatedObject bezpośrednio (abstrakcyjna klasa)" << std::endl;

    // test 2: BitmapObject
    std::cout << "\n[Test 2] BitmapObject - rysowanie bitmap" << std::endl;
    BitmapObject bitmapObj;
    std::cout << "  Utworzono BitmapObject" << std::endl;
    std::cout << "  Liczba sprite'ów: " << bitmapObj.getSpriteCount() << std::endl;
    bitmapObj.setVisible(true);
    std::cout << "  Widoczność: " << (bitmapObj.getVisible() ? "tak" : "nie") << std::endl;

    // test 3: SpriteObject
    std::cout << "\n[Test 3] SpriteObject - animacja sprite'ów" << std::endl;
    SpriteObject spriteObj;
    std::cout << "  Utworzono SpriteObject" << std::endl;
    std::cout << "  Liczba sprite'ów: " << spriteObj.getSpriteCount() << std::endl;
    std::cout << "  Aktualny sprite: " << spriteObj.getCurrentSpriteIndex() << std::endl;
    std::cout << "  Czas klatki: " << spriteObj.getFrameDuration() << " sekund" << std::endl;

    // test ustawienia czasu klatki
    std::cout << "\n[Test 4] Ustawienie parametrów animacji" << std::endl;
    spriteObj.setFrameDuration(0.2f);
    std::cout << "  Nowy czas klatki: " << spriteObj.getFrameDuration() << " sekund" << std::endl;

    // test animacji (symulacja kilku klatek)
    std::cout << "\n[Test 5] Symulacja animacji" << std::endl;
    SpriteObject animatedSprite;
    animatedSprite.setFrameDuration(0.1f);
    
    // symulujemy 5 klatek po 0.15 sekund
    for (int i = 0; i < 5; ++i) {
        std::cout << "  Klatka " << i << ", sprite: " << animatedSprite.getCurrentSpriteIndex();
        animatedSprite.animate(0.15f);
        std::cout << " -> " << animatedSprite.getCurrentSpriteIndex() << std::endl;
    }

    // test transformacji (z klasy Transformable)
    std::cout << "\n[Test 6] Transformacje (dziedziczone z Transformable)" << std::endl;
    bitmapObj.setPosition(100.0f, 200.0f);
    bitmapObj.setScale(2.0f, 2.0f);
    bitmapObj.setRotation(45.0f);
    std::cout << "  Pozycja: (100, 200)" << std::endl;
    std::cout << "  Skala: (2, 2)" << std::endl;
    std::cout << "  Rotacja: 45 stopni" << std::endl;

    std::cout << "\n=== Koniec testów ===" << std::endl;
    return 0;
}
