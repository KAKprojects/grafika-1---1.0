#include "BitmapHandler.h"
#include <algorithm>

// KONSTRUKTORY I DESTRUKTOR

BitmapHandler::BitmapHandler()
    : bitmap(), filename(""), isLoaded(false)
{
    // pusty konstruktor - bitmapa bez zawartości
}

BitmapHandler::BitmapHandler(unsigned int width, unsigned int height, const sf::Color& fillColor)
    : filename(""), isLoaded(false)
{
    // konstruktor z parametrami - tworzymy nową bitmapę
    create(width, height, fillColor);
}

BitmapHandler::~BitmapHandler()
{
    // destruktor
}

// TWORZENIE I CZYSZCZENIE

void BitmapHandler::create(unsigned int width, unsigned int height, const sf::Color& fillColor)
{
    // tworzy nową bitmapę o podanych wymiarach
    bitmap.create(width, height, fillColor);
    
    // resetuje filename, bo to nowa bitmapa
    filename = "";
    isLoaded = true;
    
    std::cout << "[BitmapHandler] Utworzono nową bitmapę: " << width << "x" << height << std::endl;
}

void BitmapHandler::clear()
{
    // zwalnia pamięć bitmapy tworząc bitmapę o wymiarach 0x0
    bitmap.create(0, 0);
    
    filename = "";
    isLoaded = false;
    
    std::cout << "[BitmapHandler] Wyczyszczono bitmapę" << std::endl;
}

//  WCZYTYWANIE I ZAPIS

bool BitmapHandler::loadFromFile(const std::string& path)
{
    // próbuje wczytać plik
    if (bitmap.loadFromFile(path)) {
        filename = path;
        isLoaded = true;
        std::cout << "[BitmapHandler] Załadowano plik: " << path << std::endl;
        std::cout << "  Wymiary: " << bitmap.getSize().x << "x" << bitmap.getSize().y << std::endl;
        return true;
    } else {
        std::cerr << "[BitmapHandler] BŁĄD: Nie udało się załadować pliku: " << path << std::endl;
        isLoaded = false;
        return false;
    }
}

bool BitmapHandler::saveToFile(const std::string& path)
{
    // sprawdza czy bitmapa zawiera dane
    if (!isLoaded || bitmap.getSize().x == 0 || bitmap.getSize().y == 0) {
        std::cerr << "[BitmapHandler] BŁĄD: Nie można zapisać pustej bitmapy" << std::endl;
        return false;
    }
    
    // próbuje zapisać do pliku
    if (bitmap.saveToFile(path)) {
        filename = path;
        std::cout << "[BitmapHandler] Zapisano plik: " << path << std::endl;
        return true;
    } else {
        std::cerr << "[BitmapHandler] BŁĄD: Nie udało się zapisać pliku: " << path << std::endl;
        return false;
    }
}

// OPERACJE NA PIKSELACH 

void BitmapHandler::setPixel(unsigned int x, unsigned int y, const sf::Color& color)
{
    // sprawdza czy współrzędne są w zakresie
    if (x < bitmap.getSize().x && y < bitmap.getSize().y) {
        bitmap.setPixel(x, y, color);
    } else {
        std::cerr << "[BitmapHandler] BŁĄD: Współrzędne poza bitmapą (" 
                  << x << ", " << y << ")" << std::endl;
    }
}

sf::Color BitmapHandler::getPixel(unsigned int x, unsigned int y) const
{
    // sprawdza czy współrzędne są w zakresie
    if (x < bitmap.getSize().x && y < bitmap.getSize().y) {
        return bitmap.getPixel(x, y);
    } else {
        std::cerr << "[BitmapHandler] BŁĄD: Współrzędne poza bitmapą (" 
                  << x << ", " << y << ")" << std::endl;
        return sf::Color::Transparent;
    }
}

void BitmapHandler::fillWithColor(const sf::Color& color)
{
    // otrzymuje wymiary
    unsigned int width = bitmap.getSize().x;
    unsigned int height = bitmap.getSize().y;
    
    // pętla przez wszystkie piksele
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            bitmap.setPixel(x, y, color);
        }
    }
    
    std::cout << "[BitmapHandler] Wypełniono bitmapę kolorem" << std::endl;
}

// OPERACJE NA BITMAPACH

void BitmapHandler::copyFrom(const BitmapHandler& source)
{
    // najpierw sprawdza czy źródło jest ważne
    if (!source.isLoaded) {
        std::cerr << "[BitmapHandler] BŁĄD: Źródło nie jest załadowane" << std::endl;
        return;
    }
    
    // tworzy nową bitmapę o takich samych wymiarach jak źródło
    bitmap.create(source.bitmap.getSize().x, source.bitmap.getSize().y);
    
    // kopiujemy każdy piksel
    for (unsigned int y = 0; y < source.bitmap.getSize().y; ++y) {
        for (unsigned int x = 0; x < source.bitmap.getSize().x; ++x) {
            bitmap.setPixel(x, y, source.bitmap.getPixel(x, y));
        }
    }
    
    // uaktualnia dane
    filename = source.filename;
    isLoaded = true;
    
    std::cout << "[BitmapHandler] Skopiowano bitmapę o wymiarach " 
              << source.bitmap.getSize().x << "x" << source.bitmap.getSize().y << std::endl;
}

void BitmapHandler::swapWith(BitmapHandler& other)
{
    // zamienia obiekty sf::Image
    std::swap(this->bitmap, other.bitmap);
    
    // zamienia informacje o plikach
    std::swap(this->filename, other.filename);
    
    // zamienia flagę loaded
    std::swap(this->isLoaded, other.isLoaded);
    
    std::cout << "[BitmapHandler] Zamieniono zawartość dwóch bitmap" << std::endl;
}

// OPERACJE GEOMETRYCZNE

void BitmapHandler::resize(unsigned int newWidth, unsigned int newHeight)
{
    // pobranie starej bitmapy
    sf::Image oldBitmap = bitmap;
    unsigned int oldWidth = oldBitmap.getSize().x;
    unsigned int oldHeight = oldBitmap.getSize().y;
    
    // tworzy nową bitmapę
    bitmap.create(newWidth, newHeight, sf::Color::Black);
    
    // kopiuje piksele ze starej bitmapy i bierze najmniejszą wartość z wymiarów żeby nie wyjść poza zakres
    unsigned int copyWidth = std::min(oldWidth, newWidth);
    unsigned int copyHeight = std::min(oldHeight, newHeight);
    
    for (unsigned int y = 0; y < copyHeight; ++y) {
        for (unsigned int x = 0; x < copyWidth; ++x) {
            bitmap.setPixel(x, y, oldBitmap.getPixel(x, y));
        }
    }
    
    std::cout << "[BitmapHandler] Zmieniono rozmiar z " << oldWidth << "x" << oldHeight 
              << " na " << newWidth << "x" << newHeight << std::endl;
}

void BitmapHandler::rotateRight90()
{
    // tworzymy nową bitmapę, wymiary są zamienione
    unsigned int width = bitmap.getSize().x;
    unsigned int height = bitmap.getSize().y;
    
    sf::Image rotated;
    rotated.create(height, width);
    
    // formuła rotacji o 90 stopni w prawo:
    // nowy_x = height - 1 - y_stary
    // nowy_y = x_stary
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int newX = height - 1 - y;
            unsigned int newY = x;
            rotated.setPixel(newX, newY, bitmap.getPixel(x, y));
        }
    }
    
    // zamienia starą bitmapę na nową
    bitmap = rotated;
    
    std::cout << "[BitmapHandler] Obrócono bitmapę o 90 stopni w prawo" << std::endl;
}

void BitmapHandler::rotateLeft90()
{
    // tworzy nową bitmapę, wymiary są zamienione
    unsigned int width = bitmap.getSize().x;
    unsigned int height = bitmap.getSize().y;
    
    sf::Image rotated;
    rotated.create(height, width);
    
    // formuła rotacji o 90 stopni w lewo:
    // nowy_x = y_stary
    // nowy_y = width - 1 - x_stary
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int newX = y;
            unsigned int newY = width - 1 - x;
            rotated.setPixel(newX, newY, bitmap.getPixel(x, y));
        }
    }
    
    // zamienia starą bitmapę na nową
    bitmap = rotated;
    
    std::cout << "[BitmapHandler] Obrócono bitmapę o 90 stopni w lewo" << std::endl;
}

void BitmapHandler::flipHorizontal()
{
    // lustrzane odbicie w poziomie (oś pionowa)
    unsigned int width = bitmap.getSize().x;
    unsigned int height = bitmap.getSize().y;
    
    sf::Image flipped;
    flipped.create(width, height);
    
    // formuła dla lustrzanego odbicia w poziomie:
    // nowy_x = width - 1 - x_stary
    // nowy_y = y_stary
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int newX = width - 1 - x;
            flipped.setPixel(newX, y, bitmap.getPixel(x, y));
        }
    }
    
    bitmap = flipped;
    
    std::cout << "[BitmapHandler] Odbito bitmapę w poziomie" << std::endl;
}

void BitmapHandler::flipVertical()
{
    // lustrzane odbicie w pionie (oś pozioma)
    unsigned int width = bitmap.getSize().x;
    unsigned int height = bitmap.getSize().y;
    
    sf::Image flipped;
    flipped.create(width, height);
    
    // formuła dla lustrzanego odbicia w pionie:
    // nowy_x = x_stary
    // nowy_y = height - 1 - y_stary
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int newY = height - 1 - y;
            flipped.setPixel(x, newY, bitmap.getPixel(x, y));
        }
    }
    
    bitmap = flipped;
    
    std::cout << "[BitmapHandler] Odbito bitmapę w pionie" << std::endl;
}

// GETTERY 

unsigned int BitmapHandler::getWidth() const
{
    return bitmap.getSize().x;
}

unsigned int BitmapHandler::getHeight() const
{
    return bitmap.getSize().y;
}

std::string BitmapHandler::getFilename() const
{
    return filename;
}

bool BitmapHandler::isValid() const
{
    return isLoaded && bitmap.getSize().x > 0 && bitmap.getSize().y > 0;
}

sf::Image& BitmapHandler::getImage()
{
    return bitmap;
}

const sf::Image& BitmapHandler::getImage() const
{
    return bitmap;
}

// INFORMACJE

void BitmapHandler::printInfo() const
{
    std::cout << " INFORMACJE O BITMAPIE " << std::endl;
    std::cout << "Wymiary: " << bitmap.getSize().x << "x" << bitmap.getSize().y << std::endl;
    std::cout << "Plik: " << (filename.empty() ? "[brak]" : filename) << std::endl;
    std::cout << "Status: " << (isLoaded ? "Załadowana" : "Pusta") << std::endl;
    std::cout << "Liczba pikseli: " << (bitmap.getSize().x * bitmap.getSize().y) << std::endl;
}
