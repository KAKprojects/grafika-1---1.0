#include "Engine.h"
#include "InputManager.h"
#include "DemoScene.h"
#include <iostream>
#include <cmath>

// ustalam �rodek
float circleX = 400;
float circleY = 400;
float speed = 250.0f; // pr�dko�� poruszania

Engine::Engine(const std::string& title, unsigned int w, unsigned int h)
    : window(sf::VideoMode(w, h), title),
      renderer(window),
      input(nullptr),
      scene(nullptr) {
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(true);
}

// zamykanie okna
// zamykanie okna
void Engine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();
        
        // Obsługa TextEntered (bardziej niezawodne)
        if (event.type == sf::Event::TextEntered) {
            unsigned int unicode = event.text.unicode;
            if (unicode >= '1' && unicode <= '6') {
                std::cout << "Mode changed to: " << (char)unicode << std::endl;
                scene->handleKeyPress(unicode);
            }
        }
        
        // Obsługa KeyPressed - backup dla klawiszy numerycznych
        if (event.type == sf::Event::KeyPressed) {
            // Bezpośrednia mapowanie klawiszy numerycznych
            switch(event.key.code) {
                case sf::Keyboard::Num1:
                    std::cout << "Mode changed to: 1" << std::endl;
                    scene->handleKeyPress('1');
                    break;
                case sf::Keyboard::Num2:
                    std::cout << "Mode changed to: 2" << std::endl;
                    scene->handleKeyPress('2');
                    break;
                case sf::Keyboard::Num3:
                    std::cout << "Mode changed to: 3" << std::endl;
                    scene->handleKeyPress('3');
                    break;
                case sf::Keyboard::Num4:
                    std::cout << "Mode changed to: 4" << std::endl;
                    scene->handleKeyPress('4');
                    break;
                case sf::Keyboard::Num5:
                    std::cout << "Mode changed to: 5" << std::endl;
                    scene->handleKeyPress('5');
                    break;
                case sf::Keyboard::Num6:
                    std::cout << "Mode changed to: 6" << std::endl;
                    scene->handleKeyPress('6');
                    break;
                default:
                    break;
            }
        }
        
        // Obsługa kliknięcia myszki
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                for (int dy = -2; dy <= 2; ++dy) {
                    for (int dx = -2; dx <= 2; ++dx) {
                        int x = pos.x + dx;
                        int y = pos.y + dy;
                        if (x >= 0 && x < 800 && y >= 0 && y < 800)
                            renderer.setPixel(x, y, sf::Color(255, 105, 180));
                    }
                }
            }
        }
    }
}

void Engine::update(float dt) {
    // Update demo scene
    if (scene) {
        scene->update(dt);
    }
    
    // poruszanie kółkiem za pomocą klawiszy strzałek
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circleY -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circleY += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) circleX -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) circleX += speed * dt;
}

// rysowanie element�w
void Engine::render() {
    // Render the demo scene
    if (scene) {
        scene->render();
    }

    // Draw the interactive circle on top
    int cx = 400, cy = 400;
    renderer.drawCircle((int)circleX, (int)circleY, 70, sf::Color(255, 192, 203), true);
    renderer.boundaryFill((int)circleX, (int)circleY, sf::Color(255, 182, 193, 200), sf::Color(255, 192, 203));

    renderer.flush();
}

void Engine::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        handleEvents();
        update(clock.restart().asSeconds());
        render();
        window.display();
    }
}

bool Engine::init() {
    input = new InputManager(window);
    scene = new DemoScene(renderer);
    scene->init();  // Initialize the demo scene
    return true;
}

void Engine::shutdown() {
    if (input) delete input;
    if (scene) delete scene;
}

void Engine::renderToFile(const std::string& filename) {
    // Renderuj bez okna graficznego - do tekstury
    sf::RenderTexture target;
    target.create(800, 600);
    
    target.clear(sf::Color(15, 0, 30));
    
    // Rysuj wszystko na teksturze
    int cx = 400, cy = 400;
    
    // Linie
    sf::VertexArray line1(sf::Lines, 2);
    line1[0] = sf::Vertex(sf::Vector2f(50, 50), sf::Color(255, 105, 180));
    line1[1] = sf::Vertex(sf::Vector2f(750, 750), sf::Color(255, 105, 180));
    target.draw(line1);
    
    sf::VertexArray line2(sf::Lines, 2);
    line2[0] = sf::Vertex(sf::Vector2f(50, 750), sf::Color(255, 20, 147));
    line2[1] = sf::Vertex(sf::Vector2f(750, 50), sf::Color(255, 20, 147));
    target.draw(line2);
    
    // Okręgi
    sf::CircleShape circle(200);
    circle.setPosition(200, 200);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color(255, 192, 203));
    circle.setOutlineThickness(1.f);
    target.draw(circle);
    
    // Elipsy (uproszczone jako obiekty)
    sf::CircleShape ellipse(250);
    ellipse.setPosition(150, 350);
    ellipse.setFillColor(sf::Color(219, 112, 147));
    ellipse.scale(1.f, 0.4f);
    target.draw(ellipse);
    
    // Koło gracza
    sf::CircleShape playerCircle(70);
    playerCircle.setPosition(circleX - 70, circleY - 70);
    playerCircle.setFillColor(sf::Color(255, 192, 203));
    target.draw(playerCircle);
    
    target.display();
    
    // Zapisz teksturę do pliku
    sf::Image img = target.getTexture().copyToImage();
    img.saveToFile(filename);
    
    std::cout << "Renderowano do: " << filename << std::endl;
}