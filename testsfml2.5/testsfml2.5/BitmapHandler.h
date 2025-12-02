#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// KLASA DO OBSŁUGI BITMAP
// podstawowe operacje: tworzenie, wczytywanie, zapis, kopiowanie
class BitmapHandler {
private:
    sf::Image bitmap;        // przechowuje dane pikseli
    std::string filename;    // nazwa pliku bieżącej bitmapy
    bool isLoaded;           // czy bitmapa jest załadowana

public:
    // KONSTRUKTORY I DESTRUKTOR
    // konstruktor - tworzy pusty obiekt
    BitmapHandler();

    // konstruktor z parametrami - tworzy bitmapę o podanych wymiarach
    BitmapHandler(unsigned int width, unsigned int height, const sf::Color& fillColor = sf::Color::Black);

    // destruktor
    ~BitmapHandler();

    // TWORZENIE I CZYSZCZENIE
    // tworzy nową bitmapę o podanych wymiarach
    // fillColor to kolor, którym zostanie wypełniona bitmapa
    void create(unsigned int width, unsigned int height, const sf::Color& fillColor = sf::Color::Black);

    // czyści bitmapę (ustawia wymiary na 0)
    void clear();

    // WCZYTYWANIE I ZAPIS
    // wczytuje bitmapę z pliku. Zwraca true jeśli OK
    bool loadFromFile(const std::string& path);

    // zapisuje bitmapę do pliku PNG. Zwraca true jeśli OK
    bool saveToFile(const std::string& path);

    // OPERACJE NA PIKSELACH
    // ustawia kolor piksela na pozycji (x, y)
    void setPixel(unsigned int x, unsigned int y, const sf::Color& color);

    // pobiera kolor piksela na pozycji (x, y)
    sf::Color getPixel(unsigned int x, unsigned int y) const;

    // wypełnia całą bitmapę jednym kolorem
    void fillWithColor(const sf::Color& color);

    // OPERACJE NA BITMAPACH
    // kopiuje zawartość innej bitmapy do tej
    // jeśli wymiary się nie zgadzają, bitmapa zostanie zmieniona
    void copyFrom(const BitmapHandler& source);

    // zamienia zawartość tej bitmapy z inną bitmapą
    void swapWith(BitmapHandler& other);

    // OPERACJE GEOMETRYCZNE
    // zmienia rozmiar bitmapy (kopiuje zawartość do nowego rozmiaru)
    void resize(unsigned int newWidth, unsigned int newHeight);

    // obraca bitmapę o 90 stopni w prawo
    void rotateRight90();

    // obraca bitmapę o 90 stopni w lewo
    void rotateLeft90();

    // odwraca bitmapę w poziomie (lustrzane odbicie)
    void flipHorizontal();

    // odwraca bitmapę w pionie (lustrzane odbicie)
    void flipVertical();

    // GETTERY
    // zwraca szerokość bitmapy
    unsigned int getWidth() const;

    // zwraca wysokość bitmapy
    unsigned int getHeight() const;

    // zwraca nazwę pliku
    std::string getFilename() const;

    // zwraca czy bitmapa jest załadowana
    bool isValid() const;

    // zwraca referencję do wewnętrznego obiektu sf::Image (do użytku z SFML)
    sf::Image& getImage();
    const sf::Image& getImage() const;

    // INFORMACJE
    // wypisuje informacje o bitmapie do konsoli
    void printInfo() const;
};
