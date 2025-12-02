#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// klasa bazowa dla wszystkich obiektów gry rysowanych za pomocą bitmap
// obsługuje wiele bitmap oraz transformacje
class BitmapObject : public sf::Drawable, public sf::Transformable {
protected:
    std::vector<sf::Texture> textures;      // tekstury wczytane z bitmap
    std::vector<sf::Sprite> sprites;        // sprite'y do rysowania
    bool isVisible;                         // czy obiekt jest widoczny

public:
    BitmapObject();
    virtual ~BitmapObject() = default;

    // załaduj bitmapę z pliku i dodaj ją jako nowy sprite
    bool addBitmapFromFile(const std::string& filePath);

    // załaduj bitmapę z obiektu sf::Image i dodaj ją jako nowy sprite
    bool addBitmapFromImage(const sf::Image& image);

    // ustaw pozycję sprite'u o danym indeksie
    void setSpritPosition(size_t index, float x, float y);

    // ustaw skalę sprite'u o danym indeksie
    void setSpriteScale(size_t index, float scaleX, float scaleY);

    // ustaw rotację sprite'u o danym indeksie (w stopniach)
    void setSpriteRotation(size_t index, float angle);

    // pobierz liczbę sprite'ów
    size_t getSpriteCount() const;

    // ustaw widoczność obiektu
    void setVisible(bool visible);

    // sprawdź czy obiekt jest widoczny
    bool getVisible() const;

    // wirtualna metoda rysowania - każdy typ obiektu może ją dostosować
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // oczyść wszystkie sprite'y i tekstury
    void clear();
};
