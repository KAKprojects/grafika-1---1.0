#include "DemoScene.h"
#include "PrimitiveRenderer.h"
#include <iostream>
#include <cmath>
#include <vector>

DemoScene::DemoScene(PrimitiveRenderer& r)
    : renderer(r)
{}

void DemoScene::init() {
    std::cout << "\n=== SILNIK GRAFIKI 2D - DEMO INTERAKTYWNE ===" << std::endl;
    std::cout << "Nacisnij klawisze 1-6 aby zmienić tryb:" << std::endl;
    std::cout << "1 - Geometria: Linie i kształty" << std::endl;
    std::cout << "2 - Animacja: Orbitujące kółka" << std::endl;
    std::cout << "3 - Wypełnione kształty: Kolory i gradienty" << std::endl;
    std::cout << "4 - Wielokąty: Złożone wzory" << std::endl;
    std::cout << "5 - Transformacje: Rotacja" << std::endl;
    std::cout << "6 - Interaktywny: Kliknij aby rysować (Strzałki do ruchu)" << std::endl;
    std::cout << "============================================\n" << std::endl;
}

void DemoScene::update(float dt) {
    t += dt;
}

void DemoScene::render() {
    renderer.clear(sf::Color(20, 15, 30));
    
    switch (mode) {
        case 1: renderModeGeometry(); break;
        case 2: renderModeAnimated(); break;
        case 3: renderModeFilled(); break;
        case 4: renderModePolygons(); break;
        case 5: renderModeTransform(); break;
        case 6: renderModeInteractive(); break;
    }
    
    renderer.flush();
}

void DemoScene::handleKeyPress(int key) {
    if (key >= '1' && key <= '6') {
        mode = key - '0';
        std::string modeNames[] = {
            "",
            "Geometria: Linie i kształty",
            "Animacja: Orbitujące kółka",
            "Wypełnione kształty: Kolory",
            "Wielokąty: Złożone wzory",
            "Transformacje: Rotacja",
            "Interaktywny: Rysowanie"
        };
        std::cout << "Zmieniono tryb na: " << modeNames[mode] << std::endl;
    }
}

// MODE 1: Basic geometry - lines and outlines
void DemoScene::renderModeGeometry() {
    int cx = 400, cy = 400;
    
    // Grid of lines
    for (int i = 50; i <= 750; i += 100) {
        renderer.drawLine(i, 50, i, 750, sf::Color(100, 50, 100), true);
        renderer.drawLine(50, i, 750, i, sf::Color(100, 50, 100), true);
    }
    
    // Main circle outline
    renderer.drawCircle(cx, cy, 150, sf::Color(200, 100, 200), false);
    
    // Nested circles
    renderer.drawCircle(cx, cy, 100, sf::Color(150, 150, 200), false);
    renderer.drawCircle(cx, cy, 50, sf::Color(100, 200, 200), false);
    
    // Ellipse outline
    renderer.drawEllipse(cx, cy, 200, 80, sf::Color(200, 150, 100), false);
    
    // Diagonal lines creating pattern
    renderer.drawLine(50, 50, 750, 750, sf::Color(150, 100, 150), true);
    renderer.drawLine(750, 50, 50, 750, sf::Color(150, 100, 150), true);
}

// MODE 2: Animated shapes moving
void DemoScene::renderModeAnimated() {
    int cx = 400, cy = 400;
    
    // Background circles
    renderer.drawCircle(cx, cy, 200, sf::Color(50, 80, 100), false);
    
    // Orbiting circles
    float angle1 = t * 1.5f;
    float angle2 = t * 2.0f;
    float angle3 = t * 0.8f;
    
    int x1 = cx + (int)(150 * cos(angle1));
    int y1 = cy + (int)(150 * sin(angle1));
    renderer.drawCircle(x1, y1, 30, sf::Color(255, 100, 150), true);
    
    int x2 = cx + (int)(200 * cos(angle2));
    int y2 = cy + (int)(200 * sin(angle2));
    renderer.drawCircle(x2, y2, 25, sf::Color(100, 200, 255), true);
    
    int x3 = cx + (int)(120 * cos(angle3));
    int y3 = cy + (int)(120 * sin(angle3));
    renderer.drawCircle(x3, y3, 20, sf::Color(255, 200, 100), true);
    
    // Center circle
    renderer.drawCircle(cx, cy, 15, sf::Color(200, 200, 200), true);
    
    // Connecting lines
    renderer.drawLine(cx, cy, x1, y1, sf::Color(100, 100, 100), true);
    renderer.drawLine(cx, cy, x2, y2, sf::Color(100, 100, 100), true);
    renderer.drawLine(cx, cy, x3, y3, sf::Color(100, 100, 100), true);
}

// MODE 3: Filled shapes with various colors
void DemoScene::renderModeFilled() {
    // Rainbow gradient circles
    renderer.drawCircle(150, 150, 80, sf::Color(255, 50, 50), true);      // Red
    renderer.drawCircle(400, 150, 80, sf::Color(255, 150, 50), true);     // Orange
    renderer.drawCircle(650, 150, 80, sf::Color(255, 255, 50), true);     // Yellow
    
    // Filled ellipses
    renderer.drawEllipse(150, 450, 120, 60, sf::Color(50, 200, 150), true);
    renderer.drawEllipse(400, 450, 150, 80, sf::Color(150, 100, 200), true);
    renderer.drawEllipse(650, 450, 100, 70, sf::Color(200, 150, 100), true);
    
    // Central filled circle
    int cx = 400, cy = 300;
    renderer.drawCircle(cx, cy, 100, sf::Color(100, 255, 200), true);
}

// MODE 4: Complex polygons and patterns
void DemoScene::renderModePolygons() {
    int cx = 400, cy = 400;
    
    // Star pattern
    std::vector<Point2D> star;
    for (int i = 0; i < 10; ++i) {
        float angle = i * 3.14159f / 5.0f;
        int radius = (i % 2 == 0) ? 180 : 90;
        star.emplace_back(
            cx + (int)(radius * cos(angle)),
            cy + (int)(radius * sin(angle))
        );
    }
    renderer.drawPolygon(star, sf::Color(255, 200, 100));
    
    // Secondary pattern - spinning squares
    float angle = t * 2.0f;
    for (int i = 0; i < 4; ++i) {
        float rot = angle + (i * 3.14159f / 2.0f);
        int x = cx + (int)(150 * cos(rot));
        int y = cy + (int)(150 * sin(rot));
        renderer.drawCircle(x, y, 30, sf::Color(100, 200, 255), true);
    }
}

// MODE 5: Transformations - rotating shapes
void DemoScene::renderModeTransform() {
    int cx = 400, cy = 400;
    
    // Rotating rings
    float angle = t * 1.5f;
    
    for (int i = 0; i < 6; ++i) {
        float rot = angle + (i * 3.14159f / 3.0f);
        int x = cx + (int)(200 * cos(rot));
        int y = cy + (int)(200 * sin(rot));
        
        renderer.drawCircle(x, y, 40, sf::Color(150 + i * 20, 100, 200), false);
        renderer.drawLine(cx, cy, x, y, sf::Color(100, 150, 200), true);
    }
    
    // Central rotating polygon
    std::vector<Point2D> polygon;
    for (int i = 0; i < 8; ++i) {
        float rot = angle + (i * 3.14159f / 4.0f);
        polygon.emplace_back(
            cx + (int)(100 * cos(rot)),
            cy + (int)(100 * sin(rot))
        );
    }
    renderer.drawPolygon(polygon, sf::Color(200, 100, 150));
}

// MODE 6: Interactive mode - shows drawing area and instructions
void DemoScene::renderModeInteractive() {
    renderer.drawLine(50, 400, 750, 400, sf::Color(80, 80, 100), true);
    renderer.drawLine(400, 50, 400, 750, sf::Color(80, 80, 100), true);
    
    // Interactive circles at corners
    renderer.drawCircle(100, 100, 40, sf::Color(255, 100, 100), true);
    renderer.drawCircle(700, 100, 40, sf::Color(100, 255, 100), true);
    renderer.drawCircle(100, 700, 40, sf::Color(100, 100, 255), true);
    renderer.drawCircle(700, 700, 40, sf::Color(255, 255, 100), true);
    
    // Central animated circle
    int cx = 400, cy = 400;
    renderer.drawCircle(cx, cy, 80, sf::Color(200, 150, 200), true);
    
    // Animated rectangle outline
    float anim = 20 + 30 * sin(t * 2.0f);
    renderer.drawLine(cx - 100 - (int)anim, cy - 100, cx + 100 + (int)anim, cy - 100, sf::Color(150, 200, 255), true);
    renderer.drawLine(cx + 100 + (int)anim, cy - 100, cx + 100 + (int)anim, cy + 100, sf::Color(150, 200, 255), true);
    renderer.drawLine(cx + 100 + (int)anim, cy + 100, cx - 100 - (int)anim, cy + 100, sf::Color(150, 200, 255), true);
    renderer.drawLine(cx - 100 - (int)anim, cy + 100, cx - 100 - (int)anim, cy - 100, sf::Color(150, 200, 255), true);
}
