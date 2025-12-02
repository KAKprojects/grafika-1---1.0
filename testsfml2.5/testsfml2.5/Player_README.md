# Klasa Player — gracz z animacją sprite'ów

## Przegląd

Klasa `Player` reprezentuje postać gracza w grze. Dziedziczy po `SpriteObject` i obsługuje:
- **Rysowanie** za pomocą sprite'ów (bitmap)
- **Animację** ruchu (zmiana sprite'ów w zależności od kierunku)
- **Ruch** gracza w czterech kierunkach (góra, dół, lewo, prawo)
- **Transformacje** (pozycja, skala, rotacja, widoczność)

## Hierarchia dziedziczenia

```
sf::Drawable
    ↑
    |
sf::Transformable
    ↑
    |
BitmapObject ←─────────── AnimatedObject
    ↑                           ↑
    |                           |
SpriteObject ──────────────────┘
    ↑
    |
Player
```

## Interfejs klasy

### Konstruktor
```cpp
Player();
```

### Wczytywanie sprite'ów
```cpp
bool Player::loadSprites(const std::string& spritesDir);
```
- Wczytuje sprite'y z katalogu: `player_up_0.png`, `player_down_0.png`, `player_left_0.png`, `player_right_0.png`, `player_idle_0.png`
- Każdy sprite reprezentuje gracza patrującego w danym kierunku
- Zwraca `true` jeśli wszystkie sprite'y załadowały się pomyślnie

### Kierunek i ruch
```cpp
void Player::setDirection(PlayerDirection direction);
PlayerDirection Player::getDirection() const;

void Player::moveInDirection(PlayerDirection direction, float deltaTime);
void Player::stop();
```

- `PlayerDirection` — enum: `UP`, `DOWN`, `LEFT`, `RIGHT`, `IDLE`
- `setDirection()` — zmienia kierunek i sprite
- `moveInDirection()` — zmienia pozycję i kierunek
- `stop()` — zatrzymuje gracza (przełącza na sprite IDLE)

### Prędkość
```cpp
void Player::setSpeed(float newSpeed);
float Player::getSpeed() const;
```

- Prędkość w pikselach na sekundę (domyślnie 150)

### Animacja
```cpp
virtual void Player::animate(float deltaTime) override;
```

- Aktualizuje animację sprite'ów
- Wywołuje wirtualną metodę z `SpriteObject`

### Informacje
```cpp
void Player::printInfo() const;
```

- Wypisuje pozycję, kierunek, sprite, itd.

## Typ wyliczeniowy

```cpp
enum class PlayerDirection {
    UP,      // góra
    DOWN,    // dół
    LEFT,    // lewo
    RIGHT,   // prawo
    IDLE     // stanie na miejscu
};
```

## Transformacje (z klasy Transformable)

```cpp
player.setPosition(x, y);           // pozycja
player.setScale(scaleX, scaleY);    // skala
player.setRotation(angle);          // rotacja (stopnie)

player.setVisible(bool);            // widoczność
bool visible = player.getVisible();
```

## Sprite'y

Player oczekuje 5 plików PNG w katalogu `spritesDir`:

| Plik | Kierunek | Znaczenie |
|------|----------|-----------|
| `player_up_0.png` | UP | gracz patrzący w górę |
| `player_down_0.png` | DOWN | gracz patrzący w dół |
| `player_left_0.png` | LEFT | gracz patrzący w lewo |
| `player_right_0.png` | RIGHT | gracz patrzący w prawo |
| `player_idle_0.png` | IDLE | gracz stojący (opcjonalnie) |

Każdy sprite powinien być obrazem 32x32 lub większym (wymiary dostosowujesz w kodzie).

### Generowanie sprite'ów

Darmowe zasoby do sprite'ów:
- **OpenGameArt.org** — https://opengameart.org/ (sprite sheets, characters)
- **itch.io** — https://itch.io/game-assets/free (bezpłatne asset paki)
- **Kenney.nl** — https://kenney.nl/assets (free pixel art)

Alternatywnie, można użyć narzędzi takich jak:
- **Aseprite** — pixel art editor
- **Piskel** — darmowy online pixel art tool
- **ImageMagick** — generowanie sprite'ów programowo

## Przykład użycia

### Inicjalizacja
```cpp
Player player;
player.setPosition(400, 300);
player.setSpeed(200);  // piksele na sekundę

// wczytaj sprite'y
if (!player.loadSprites("./sprites")) {
    std::cerr << "Błąd wczytywania sprite'ów!" << std::endl;
}
```

### Pętla gry
```cpp
sf::Clock clock;

while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    // obsługa klawiatury
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player.moveInDirection(PlayerDirection::UP, deltaTime);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player.moveInDirection(PlayerDirection::DOWN, deltaTime);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.moveInDirection(PlayerDirection::LEFT, deltaTime);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.moveInDirection(PlayerDirection::RIGHT, deltaTime);
    } else {
        player.stop();
    }

    // zaktualizuj animację
    player.animate(deltaTime);

    // rysowanie
    window.clear();
    window.draw(player);  // Player dziedziczy po Drawable
    window.display();
}
```

### Transformacje
```cpp
player.setScale(1.5f, 1.5f);        // powiększenie
player.setRotation(45.0f);          // obrót
player.setVisible(false);           // ukrycie
```

## Cechy implementacji

1. **Dziedziczenie**: klasa dziedziczy po `SpriteObject`, który zapewnia:
   - Obsługę sprite'ów (`BitmapObject`)
   - Obsługę animacji (`AnimatedObject`)
   - Transformacje (`sf::Transformable`)
   - Renderowanie (`sf::Drawable`)

2. **Kierunki ruchu**: enum `PlayerDirection` ułatwia obsługę klawiatury

3. **Animacja**: automatyczna zmiana sprite'ów w zależności od kierunku

4. **Fallback**: jeśli sprite'y nie załadują się, gracz używa sprite'ów domyślnych

## Testowanie

```bash
g++ -std=c++17 -c Player.cpp $(pkg-config --cflags sfml-graphics) -o Player.o
g++ -std=c++17 -c BitmapObject.cpp $(pkg-config --cflags sfml-graphics) -o BitmapObject.o
g++ -std=c++17 -c SpriteObject.cpp $(pkg-config --cflags sfml-graphics) -o SpriteObject.o
g++ -std=c++17 PlayerTest.cpp Player.o BitmapObject.o SpriteObject.o \
    $(pkg-config --cflags --libs sfml-graphics) -o test_player
./test_player
```

## Pliki

- `Player.h` / `Player.cpp` — implementacja klasy
- `PlayerTest.cpp` — testy
- `sprites/` — katalog z sprite'ami

