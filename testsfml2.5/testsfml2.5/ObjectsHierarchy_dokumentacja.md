# Hierarchia klas silnika gry — AnimatedObject, BitmapObject, SpriteObject

## Przegląd

Rozszerzona hierarchia klas silnika gry umożliwia tworzenie:
- obiektów do animowania (interfejs `AnimatedObject`)
- obiektów rysowanych za pomocą bitmap (klasa `BitmapObject`)
- obiektów animowanych sprite'ów (klasa `SpriteObject`)

## Klasa `AnimatedObject`

**Cel**: abstrakcyjna klasa bazowa dla wszystkich obiektów, które mogą być animowane.

**Interfejs**:
```cpp
class AnimatedObject {
public:
    virtual ~AnimatedObject() = default;
    virtual void animate(float deltaTime) = 0;
};
```

**Opis**:
- Definiuje abstrakcyjną metodę `animate(float deltaTime)` — każda klasa pochodna musi ją zaimplementować
- `deltaTime` to czas upłynięty od ostatniej klatki (w sekundach)
- Pozwala na ujednolicenie interfejsu dla wszystkich animowalnych obiektów

**Zastosowanie**:
```cpp
class MyAnimatedObject : public AnimatedObject {
public:
    void animate(float deltaTime) override {
        // tutaj logika animacji
    }
};
```

---

## Klasa `BitmapObject`

**Cel**: klasa bazowa dla obiektów rysowanych za pomocą bitmap; obsługuje wiele sprite'ów i transformacje.

**Dziedziczenie**: publiczne po `sf::Drawable` i `sf::Transformable`

**Cechy**:
- Może zawierać wiele bitmap (sprite'ów) jednocześnie
- Obsługuje transformacje (pozycja, skala, rotacja) dzięki `sf::Transformable`
- Możliwość rysowania w `sf::RenderWindow` dzięki `sf::Drawable`

**Interfejs**:
```cpp
class BitmapObject : public sf::Drawable, public sf::Transformable {
public:
    bool addBitmapFromFile(const std::string& filePath);
    bool addBitmapFromImage(const sf::Image& image);
    
    void setSpritPosition(size_t index, float x, float y);
    void setSpriteScale(size_t index, float scaleX, float scaleY);
    void setSpriteRotation(size_t index, float angle);
    
    size_t getSpriteCount() const;
    void setVisible(bool visible);
    bool getVisible() const;
    void clear();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
```

**Metody**:
- `addBitmapFromFile(path)` — wczytuje plik graficzny i dodaje go jako sprite
- `addBitmapFromImage(image)` — dodaje sprite na podstawie obiektu `sf::Image`
- `setSpritPosition/Scale/Rotation(index, ...)` — ustawia transformacje dla konkretnego sprite'u
- `getSpriteCount()` — zwraca liczbę sprite'ów
- `setVisible(bool)` / `getVisible()` — kontroluje widoczność obiektu
- `draw()` — rysuje wszystkie sprite'y (implementacja wirtualna)
- `clear()` — usuwa wszystkie sprite'y i tekstury

**Transformacje** (z `sf::Transformable`):
- `setPosition(x, y)`
- `setScale(scaleX, scaleY)`
- `setRotation(angle)` — kąt w stopniach
- itp.

**Przykład**:
```cpp
BitmapObject obj;
obj.addBitmapFromFile("character.png");
obj.addBitmapFromFile("shadow.png");

obj.setPosition(100, 200);
obj.setScale(2.0f, 2.0f);

// rysowanie
window.draw(obj);
```

---

## Klasa `SpriteObject`

**Cel**: klasa dla obiektów animowanych sprite'ów — łączy rysowanie bitmap i animację.

**Dziedziczenie**: publiczne po `BitmapObject` i `AnimatedObject`

**Cechy**:
- Obsługuje animacje na zasadzie przełączania sprite'ów (sprite sheet animation)
- Każdy sprite wyświetlany przez określony czas (`frameDuration`)
- Automatyczne przechodzenie do następnego sprite'u w pętli

**Interfejs**:
```cpp
class SpriteObject : public BitmapObject, public AnimatedObject {
public:
    void setCurrentSprite(size_t index);
    size_t getCurrentSpriteIndex() const;
    
    void setFrameDuration(float duration);
    float getFrameDuration() const;
    
    void resetAnimationTimer();
    
    virtual void animate(float deltaTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
```

**Metody**:
- `setCurrentSprite(index)` — ustawia aktualnie wyświetlany sprite
- `getCurrentSpriteIndex()` — zwraca indeks aktualnego sprite'u
- `setFrameDuration(duration)` — ustawia czas wyświetlania każdej klatki (w sekundach)
- `getFrameDuration()` — zwraca czas klatki
- `resetAnimationTimer()` — resetuje timer animacji
- `animate(deltaTime)` — zmienia sprite w zależności od upłynięcia czasu
- `draw()` — rysuje tylko aktualnie wybrany sprite

**Mechanika animacji**:
1. Timer animacji akumuluje `deltaTime`
2. Gdy timer osiągnie `frameDuration`, sprite zmienia się na następny
3. Indeksy sprite'ów przechodzą cyklicznie (0 → 1 → ... → N-1 → 0)

**Przykład**:
```cpp
SpriteObject robot;

// wczytaj klatki animacji
for (int i = 1; i <= 4; ++i) {
    robot.addBitmapFromFile("robot_frame_" + std::to_string(i) + ".png");
}

// ustaw czas każdej klatki
robot.setFrameDuration(0.2f);  // 0.2 sekundy na klatkę

// w głównej pętli gry
void gameLoop(float deltaTime) {
    robot.animate(deltaTime);    // zaktualizuj animację
    window.draw(robot);          // rysuj bieżący sprite
}
```

---

## Hierarchia dziedziczenia (diagram)

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
    └─────────── SpriteObject ──┘
                (wielodziedziczenie)
```

---

## Uwagi praktyczne

1. **Wiele bitmap w BitmapObject**: przydatne dla obiektów składających się z wielu warstw (np. postać + cień + akcesoria).

2. **Animacja sprite'ów**: `SpriteObject` rysuje **tylko** aktualny sprite, ale przechowuje wszystkie sprite'y. Transformacje obiekt u (pozycja, skala, rotacja) dotyczą rysowanego sprite'u.

3. **Dziedziczenie wielorakie w SpriteObject**: bezpieczne dzięki wirtualnym destruktorom i separacji interfejsów.

4. **Performance**: `BitmapObject.draw()` rysuje **wszystkie** sprite'y, `SpriteObject.draw()` rysuje **jeden** sprite — to oszczędza wydajność.

---

## Testowanie

Test (`ObjectsHierarchyTest.cpp`) weryfikuje:
- Instancjowanie każdej klasy
- Ustawienie parametrów
- Symulację animacji (przełączanie sprite'ów w czasie)
- Dziedziczenie transformacji

Kompilacja i uruchamianie:
```bash
g++ -std=c++17 -c BitmapObject.cpp $(pkg-config --cflags sfml-graphics) -o BitmapObject.o
g++ -std=c++17 -c SpriteObject.cpp $(pkg-config --cflags sfml-graphics) -o SpriteObject.o
g++ -std=c++17 ObjectsHierarchyTest.cpp BitmapObject.o SpriteObject.o $(pkg-config --cflags --libs sfml-graphics) -o test_hierarchy
./test_hierarchy
```

---

## Pliki

- `AnimatedObject.h` — interfejs abstrakcyjny
- `BitmapObject.h` / `BitmapObject.cpp` — klasa do rysowania bitmap
- `SpriteObject.h` / `SpriteObject.cpp` — klasa do animacji sprite'ów
- `ObjectsHierarchyTest.cpp` — testy

