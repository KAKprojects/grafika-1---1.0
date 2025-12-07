#include "DemoScene.h"
#include "PrimitiveRenderer.h"

DemoScene::DemoScene(PrimitiveRenderer& r)
    : renderer(r)
{}

void DemoScene::init() {
    // placeholder
}

void DemoScene::update(float dt) {
    t += dt;
}

void DemoScene::render() {
    // draw some primitives to showcase functionality
    int cx = 400, cy = 400;
    renderer.clear(sf::Color(10,10,20));
    renderer.drawLine(50, 50, 750, 750, sf::Color::Red, true);
    renderer.drawCircle(cx, cy, 100, sf::Color::Green, true);
    renderer.drawEllipse(cx, cy, 200, 80, sf::Color::Blue, true);
    renderer.flush();
}
