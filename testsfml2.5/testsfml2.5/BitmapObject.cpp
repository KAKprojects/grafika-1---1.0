#include "BitmapObject.h"
#include <iostream>

BitmapObject::BitmapObject()
    : isVisible(true)
{
    // pusty konstruktor - sprite'y będą dodawane dynamicznie
}

bool BitmapObject::addBitmapFromFile(const std::string& filePath)
{
    // wczytaj teksturę z pliku
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "[BitmapObject] Błąd: nie udało się wczytać pliku: " << filePath << std::endl;
        return false;
    }

    // dodaj teksturę do wektora
    textures.push_back(texture);

    // utwórz sprite na podstawie tekstury
    sf::Sprite sprite(textures.back());
    sprites.push_back(sprite);

    std::cout << "[BitmapObject] Dodano bitmapę z pliku: " << filePath << std::endl;
    return true;
}

bool BitmapObject::addBitmapFromImage(const sf::Image& image)
{
    // utwórz teksturę z obrazu
    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cerr << "[BitmapObject] Błąd: nie udało się załadować tekstury z obrazu" << std::endl;
        return false;
    }

    // dodaj teksturę do wektora
    textures.push_back(texture);

    // utwórz sprite na podstawie tekstury
    sf::Sprite sprite(textures.back());
    sprites.push_back(sprite);

    std::cout << "[BitmapObject] Dodano bitmapę z obiektu sf::Image" << std::endl;
    return true;
}

void BitmapObject::setSpritPosition(size_t index, float x, float y)
{
    if (index < sprites.size()) {
        sprites[index].setPosition(x, y);
    } else {
        std::cerr << "[BitmapObject] Błąd: indeks sprite'u poza zakresem" << std::endl;
    }
}

void BitmapObject::setSpriteScale(size_t index, float scaleX, float scaleY)
{
    if (index < sprites.size()) {
        sprites[index].setScale(scaleX, scaleY);
    } else {
        std::cerr << "[BitmapObject] Błąd: indeks sprite'u poza zakresem" << std::endl;
    }
}

void BitmapObject::setSpriteRotation(size_t index, float angle)
{
    if (index < sprites.size()) {
        sprites[index].setRotation(angle);
    } else {
        std::cerr << "[BitmapObject] Błąd: indeks sprite'u poza zakresem" << std::endl;
    }
}

size_t BitmapObject::getSpriteCount() const
{
    return sprites.size();
}

void BitmapObject::setVisible(bool visible)
{
    isVisible = visible;
}

bool BitmapObject::getVisible() const
{
    return isVisible;
}

void BitmapObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!isVisible) {
        return;
    }

    // stosuj transformacje obiektu do wszystkich sprite'ów
    states.transform *= getTransform();

    // rysuj wszystkie sprite'y
    for (const auto& sprite : sprites) {
        target.draw(sprite, states);
    }
}

void BitmapObject::clear()
{
    sprites.clear();
    textures.clear();
    std::cout << "[BitmapObject] Wyczyszczono wszystkie sprite'y i tekstury" << std::endl;
}
