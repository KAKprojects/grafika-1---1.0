// przykłady użycia klasy BitmapHandler
// ten plik pokazuje jak używać dostępnych funkcji

#include "BitmapHandler.h"

int main() {
    std::cout << "TEST KLASY BITMAPHANDLER" << std::endl;
    
    // TESTY TWORZENIA
    std::cout << "\n1. Tworzenie bitmapy..." << std::endl;
    BitmapHandler bitmap1(100, 100, sf::Color::Red);
    bitmap1.printInfo();
    
    // TESTY OPERACJI NA PIKSELACH
    std::cout << "2. Operacje na pikselach..." << std::endl;
    bitmap1.setPixel(10, 10, sf::Color::Green);
    bitmap1.setPixel(20, 20, sf::Color::Blue);
    sf::Color pixelColor = bitmap1.getPixel(10, 10);
    std::cout << "Kolor piksela (10,10): R=" << (int)pixelColor.r 
              << " G=" << (int)pixelColor.g << " B=" << (int)pixelColor.b << std::endl;
    
    // TESTY WYPEŁNIANIA
    std::cout << "\n3. Wypełnianie kolorem..." << std::endl;
    BitmapHandler bitmap2(50, 50);
    bitmap2.fillWithColor(sf::Color::Cyan);
    bitmap2.printInfo();
    
    // TESTY KOPIOWANIA
    std::cout << "\n4. Kopiowanie bitmapy..." << std::endl;
    BitmapHandler bitmap3;
    bitmap3.copyFrom(bitmap1);
    bitmap3.printInfo();
    
    // TESTY ZAMIANY
    std::cout << "\n5. Zamiana zawartości..." << std::endl;
    std::cout << "Przed zamianą:" << std::endl;
    std::cout << "  bitmap1: " << bitmap1.getWidth() << "x" << bitmap1.getHeight() << std::endl;
    std::cout << "  bitmap2: " << bitmap2.getWidth() << "x" << bitmap2.getHeight() << std::endl;
    
    bitmap1.swapWith(bitmap2);
    
    std::cout << "Po zamianie:" << std::endl;
    std::cout << "  bitmap1: " << bitmap1.getWidth() << "x" << bitmap1.getHeight() << std::endl;
    std::cout << "  bitmap2: " << bitmap2.getWidth() << "x" << bitmap2.getHeight() << std::endl;
    
    // TESTY ZMIANY ROZMIARU
    std::cout << "\n6. Zmiana rozmiaru..." << std::endl;
    BitmapHandler bitmap4(100, 80);
    bitmap4.fillWithColor(sf::Color::Yellow);
    bitmap4.printInfo();
    
    bitmap4.resize(150, 120);
    bitmap4.printInfo();
    
    // TESTY ROTACJI
    std::cout << "\n7. Rotacja..." << std::endl;
    BitmapHandler bitmap5(120, 80);
    std::cout << "Wymiary przed rotacją: " << bitmap5.getWidth() << "x" << bitmap5.getHeight() << std::endl;
    
    bitmap5.rotateRight90();
    std::cout << "Wymiary po rotacji o 90 stopni w prawo: " << bitmap5.getWidth() << "x" << bitmap5.getHeight() << std::endl;
    
    bitmap5.rotateLeft90();
    std::cout << "Wymiary po rotacji o 90 stopni w lewo: " << bitmap5.getWidth() << "x" << bitmap5.getHeight() << std::endl;
    
    // TESTY ODBICIA
    std::cout << "\n8. Odbicia..." << std::endl;
    BitmapHandler bitmap6(100, 100);
    bitmap6.fillWithColor(sf::Color::Magenta);
    
    bitmap6.flipHorizontal();
    bitmap6.flipVertical();
    bitmap6.printInfo();
    
    // TESTY GETTERY
    std::cout << "\n9. Gettery..." << std::endl;
    std::cout << "Szerokość: " << bitmap1.getWidth() << std::endl;
    std::cout << "Wysokość: " << bitmap1.getHeight() << std::endl;
    std::cout << "Czy ważna: " << (bitmap1.isValid() ? "Tak" : "Nie") << std::endl;
    
    // TESTY CZYSZCZENIA
    std::cout << "\n10. Czyszczenie..." << std::endl;
    bitmap1.clear();
    bitmap1.printInfo();
    
    std::cout << "\nKONIEC TESTÓW" << std::endl;
    return 0;
}
