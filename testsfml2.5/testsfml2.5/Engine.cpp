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
void Engine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();
        
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
    // poruszanie kółkiem za pomocą klawiszy strzałek
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circleY -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circleY += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) circleX -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) circleX += speed * dt;
}

// rysowanie element�w
void Engine::render() {
    renderer.clear(sf::Color(15, 0, 30));

    int cx = 400, cy = 400;

    // 1. linie
    renderer.drawLine(50, 50, 750, 750, sf::Color(255, 105, 180), true);
        renderer.drawLine(50, 750, 750, 50, sf::Color(255, 20, 147), false);
    renderer.drawLine(50, cy, 750, cy, sf::Color(255, 182, 193), true);
    renderer.drawLine(cx, 50, cx, 750, sf::Color(255, 182, 193), true);

    // 2. okr�gi
    renderer.drawCircle(cx, cy, 200, sf::Color(255, 192, 203), true);
    renderer.drawCircle(cx, cy, 150, sf::Color(255, 160, 200), false);

    // 3. elipsy
    renderer.drawEllipse(cx, cy, 250, 100, sf::Color(219, 112, 147), true);
    renderer.drawEllipse(cx, cy, 100, 180, sf::Color(255, 105, 180), true);

    // 4. k�ko
    renderer.drawCircle((int)circleX, (int)circleY, 70, sf::Color(255, 192, 203), true);
    renderer.boundaryFill((int)circleX, (int)circleY, sf::Color(255, 182, 193, 200), sf::Color(255, 192, 203));

    // 5.gwiazda
    float r = 180;
    std::vector<Point2D> star;
    for (int i = 0; i < 10; ++i) {
        float angle = i * 3.14159f / 5.0f;
        int radius = (i % 2 == 0) ? (int)r : (int)(r * 0.5f);
        star.emplace_back(cx + (int)(radius * cos(angle)), cy + (int)(radius * sin(angle)));
    }
    renderer.drawPolygon(star, sf::Color(255, 220, 230));

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