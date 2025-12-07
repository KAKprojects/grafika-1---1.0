#pragma once
#include <SFML/Graphics.hpp>
#include "PrimitiveRenderer.h"
#include "InputManager.h"
#include "DemoScene.h"

class Engine {
    sf::RenderWindow window;
    PrimitiveRenderer renderer;
    InputManager* input;
    DemoScene* scene;

    void handleEvents();
    void handleInput();
    void update(float dt);
    void render();

public:
    Engine(const std::string& title = "Silnik 2D ", unsigned int w = 800, unsigned int h = 600);
    bool init();
    void run(); // uruchamia
    void shutdown();
    void renderToFile(const std::string& filename); // renderuj scenę do PNG
};