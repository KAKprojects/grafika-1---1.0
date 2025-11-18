#pragma once
#include <SFML/Graphics.hpp>
#include "PrimitiveRenderer.h"

class Engine {
    sf::RenderWindow window;
    PrimitiveRenderer renderer;

    void handleEvents(); // sprawdza czy zamknê³am
    void update(float dt);
    void render();

public:
    Engine(const std::string& title = "Silnik 2D ", unsigned int w = 800, unsigned int h = 600);
    void run(); // uruchamia
};