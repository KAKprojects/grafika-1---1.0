#pragma once

// klasa bazowa dla wszystkich obiektów gry, które mogą być animowane
class AnimatedObject {
public:
    virtual ~AnimatedObject() = default;

    // abstrakcyjna metoda animacji - każdy animowany obiekt musi ją zaimplementować
    virtual void animate(float deltaTime) = 0;
};
