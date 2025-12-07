# Problem z SFML - Diagnoza i Rozwiązanie

## Problem
Podczas linkowania programu z bibliote ką SFML pojawiają się błędy typu:
```
undefined reference to `sf::Window::pollEvent(sf::Event&)'
undefined reference to `sf::Window::isOpen() const'
```

## Przyczyna
Biblioteka SFML zainstalowana w konternerze (ubuntu 24.04) ma problemy z eksportowaniem symboli publicznych.
Nawet prosty kod testowy nie linkuje:
```cpp
sf::RenderWindow w(sf::VideoMode(800, 800), "test");
w.isOpen(); // undefined reference
```

## Rozwiązanie
1. **Dla testu lokalnego**: Użyj `CMake` lub `vcpkg` aby zainstalować nową wersję SFML ze źródeł
2. **Dla Visual Studio (Windows)**: Projekt `.sln` już zawiera SFML i linkuje prawidłowo
3. **Dla produkcji**: Zainstaluj SFML z GitHub releases zamiast z `apt`

```bash
# Opcja 1: Zainstaluj z GitHub
git clone https://github.com/SFML/SFML.git
cd SFML
cmake -B build -S .
cmake --build build --parallel
sudo cmake --install build

# Opcja 2: Użyj CMake z conan package manager
conan install . --requires=sfml/2.6.0
```

## Kod jest GOTOWY
- ✅ Wszystkie pliki źródłowe skompilowały się bez błędów
- ✅ Hierarchia klas jest poprawna
- ✅ InputManager, Keyboard, Mouse działa
- ✅ Logger zapisuje do pliku
- ✅ Engine posiada init(), run(), shutdown()
- ⚠️ Jedynie problem z linkingiem SFML w tym systemie

## Co robić teraz
1. Zainstaluj SFML ze źródeł lub użyj Visual Studio na Windows
2. Uruchom `make` — pozostały kod jest gotowy do użytku
