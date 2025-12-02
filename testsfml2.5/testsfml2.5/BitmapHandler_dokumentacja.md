# Klasa BitmapHandler - Dokumentacja

## Wprowadzenie

Klasa `BitmapHandler` to narzędzie do obsługi bitmap w projekcie graficznym. Pozwala na:
- Tworzenie nowych bitmap
- Wczytywanie i zapisywanie plików
- Manipulację poszczególnymi pikselami
- Operacje geometryczne (rotacja, odbicie, zmiana rozmiaru)
- Kopiowanie i zamienianie bitmap

## Instalacja i Kompilacja

Aby używać `BitmapHandler`, dołącz do projektu:
- `BitmapHandler.h` - plik nagłówkowy
- `BitmapHandler.cpp` - implementacja

Upewnij się, że masz zainstalowaną bibliotekę SFML 2.6.

Kompilacja:
```bash
g++ -c BitmapHandler.cpp -o BitmapHandler.o -std=c++17 $(pkg-config --cflags sfml-graphics)
```

## Podstawowe Przykłady

### Przykład 1: Tworzenie Bitmapy

```cpp
#include "BitmapHandler.h"

int main() {
    // Tworzy bitmapę 400x300 pikseli, wypełnioną na czarno
    BitmapHandler bitmap(400, 300, sf::Color::Black);
    
    // Lub można stworzyć pustą bitmapę
    BitmapHandler emptyBitmap;
    emptyBitmap.create(800, 600, sf::Color::White);
    
    return 0;
}
```

### Przykład 2: Praca z Pikselami

```cpp
BitmapHandler bitmap(100, 100);

// Ustawianie koloru piksela
bitmap.setPixel(50, 50, sf::Color::Red);
bitmap.setPixel(51, 50, sf::Color::Green);
bitmap.setPixel(52, 50, sf::Color::Blue);

// Pobieranie koloru piksela
sf::Color color = bitmap.getPixel(50, 50);
std::cout << "R: " << (int)color.r << " G: " << (int)color.g << " B: " << (int)color.b << std::endl;

// Wypełnienie całej bitmapy kolorem
bitmap.fillWithColor(sf::Color::Cyan);
```

### Przykład 3: Wczytywanie i Zapisywanie

```cpp
BitmapHandler bitmap;

// Wczytywanie z pliku
if (bitmap.loadFromFile("./images/moj_obraz.png")) {
    std::cout << "Pomyślnie załadowana bitmap" << std::endl;
    bitmap.printInfo();
} else {
    std::cout << "Błąd przy wczytywaniu" << std::endl;
}

// Zapisywanie do pliku
if (bitmap.saveToFile("./output/wynik.png")) {
    std::cout << "Pomyślnie zapisana bitmap" << std::endl;
}
```

### Przykład 4: Kopiowanie Bitmap

```cpp
BitmapHandler original(200, 200);
original.fillWithColor(sf::Color::Yellow);

// kopiujemy oryginalną bitmapę
BitmapHandler copy;
copy.copyFrom(original);

// teraz `copy` ma takie same wymiary i kolory jak `original`
copy.printInfo();
```

### Przykład 5: Zamienianie Bitmap

```cpp
BitmapHandler bitmap1(100, 100, sf::Color::Red);
BitmapHandler bitmap2(200, 200, sf::Color::Blue);

std::cout << "Przed zamianą:" << std::endl;
std::cout << "bitmap1: " << bitmap1.getWidth() << "x" << bitmap1.getHeight() << std::endl;
std::cout << "bitmap2: " << bitmap2.getWidth() << "x" << bitmap2.getHeight() << std::endl;

// Zamieniamy zawartość
bitmap1.swapWith(bitmap2);

std::cout << "Po zamianie:" << std::endl;
std::cout << "bitmap1: " << bitmap1.getWidth() << "x" << bitmap1.getHeight() << std::endl;
std::cout << "bitmap2: " << bitmap2.getWidth() << "x" << bitmap2.getHeight() << std::endl;
```

### Przykład 6: Operacje Geometryczne

```cpp
BitmapHandler bitmap(200, 100);
bitmap.fillWithColor(sf::Color::Green);

// Zmiana rozmiaru
bitmap.resize(300, 150);

// Rotacja
bitmap.rotateRight90();   // Obrót o 90 stopni w prawo
bitmap.rotateLeft90();    // Obrót o 90 stopni w lewo

// Odbicia (lustrzane refleksje)
bitmap.flipHorizontal();  // Odbicie w poziomie
bitmap.flipVertical();    // Odbicie w pionie
```

### Przykład 7: Informacje o Bitmapie

```cpp
BitmapHandler bitmap;
bitmap.loadFromFile("./images/obraz.png");

// Pobieranie informacji
unsigned int width = bitmap.getWidth();
unsigned int height = bitmap.getHeight();
std::string filename = bitmap.getFilename();
bool valid = bitmap.isValid();

// Wypisanie wszystkich informacji
bitmap.printInfo();
```

### Przykład 8: Dostęp do Wewnętrznego Obiektu SFML

```cpp
BitmapHandler bitmap(400, 300);

// Jeśli chcesz pracować bezpośrednio z SFML Image
sf::Image& sfmlImage = bitmap.getImage();

// Możesz używać wszystkich metod SFML
// ale pamiętaj aby nie modyfikować wymiarów bezpośrednio!
```

## Referencja Funkcji

### Konstruktory
- `BitmapHandler()` - Tworzy pusty handler
- `BitmapHandler(width, height, color)` - Tworzy bitmapę o podanych wymiarach

### Tworzenie i Czyszczenie
- `void create(width, height, color)` - Tworzy nową bitmapę
- `void clear()` - Czyści bitmapę (0x0)

### Wczytywanie i Zapis
- `bool loadFromFile(path)` - Wczytuje plik PNG
- `bool saveToFile(path)` - Zapisuje do pliku PNG

### Piksele
- `void setPixel(x, y, color)` - Ustawia kolor piksela
- `sf::Color getPixel(x, y)` - Pobiera kolor piksela
- `void fillWithColor(color)` - Wypełnia całą bitmapę kolorem

### Operacje na Bitmapach
- `void copyFrom(source)` - Kopiuje inną bitmapę
- `void swapWith(other)` - Zamienia zawartość z inną bitmapą

### Operacje Geometryczne
- `void resize(width, height)` - Zmienia rozmiar
- `void rotateRight90()` - Obrót o 90 stopni w prawo
- `void rotateLeft90()` - Obrót o 90 stopni w lewo
- `void flipHorizontal()` - Odbicie w poziomie
- `void flipVertical()` - Odbicie w pionie

### Gettery
- `unsigned int getWidth()` - Zwraca szerokość
- `unsigned int getHeight()` - Zwraca wysokość
- `std::string getFilename()` - Zwraca nazwę pliku
- `bool isValid()` - Sprawdza czy bitmap jest ważna
- `sf::Image& getImage()` - Zwraca referencję do SFML Image

### Informacje
- `void printInfo()` - Wypisuje informacje do konsoli

## Ważne Uwagi

1. **Bezpieczeństwo Granic**: Funkcje `setPixel` i `getPixel` sprawdzają czy współrzędne są w zakresie
2. **Operacje Geometryczne**: Rotacja i odbicia tworzy nową bitmapę, więc wymaga czasu obliczeniowego
3. **Wczytywanie Plików**: Wspiera tylko formaty obsługiwane przez SFML (PNG, JPG, BMP, etc.)
4. **Komunikaty**: Klasa wypisuje komunikaty do konsoli przy każdej operacji

## Kolory SFML

```cpp
sf::Color::Black       // Czarny (0, 0, 0)
sf::Color::White       // Biały (255, 255, 255)
sf::Color::Red         // Czerwony (255, 0, 0)
sf::Color::Green       // Zielony (0, 255, 0)
sf::Color::Blue        // Niebieski (0, 0, 255)
sf::Color::Yellow      // Żółty (255, 255, 0)
sf::Color::Cyan        // Cyjan (0, 255, 255)
sf::Color::Magenta     // Magenta (255, 0, 255)
sf::Color::Transparent // Przezroczysty (0, 0, 0, 0)

// Lub stwórz własny
sf::Color mojKolor(200, 100, 50);        // RGB
sf::Color mojKolorAlpha(200, 100, 50, 128);  // RGBA (z przezroczystością)
```

## Rozwiązywanie Problemów

### Problem: "Nie udało się załadować pliku"
- Sprawdź czy plik istnieje
- Sprawdź ścieżkę (może być względna do bieżącego katalogu)
- Sprawdź czy format jest obsługiwany (PNG, JPG, BMP)

### Problem: Program działa wolno przy dużych bitmapach
- Operacje na pikselach w pętlach są wolne
- Zmiana rozmiaru tworzy kopię całej bitmapy
- Rozważ zmniejszenie rozmiaru lub optymalizację kodu

### Problem: Segmentation Fault
- Sprawdź czy bitmap jest załadowana przed użyciem
- Sprawdź czy współrzędne są w zakresie
- Używaj `isValid()` do sprawdzenia stanu bitmapy
