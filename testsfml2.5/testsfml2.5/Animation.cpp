#include "Animation.h"
#include "PrimitiveRenderer.h"

Animation::Animation(float frameTime_)
    : frameTime(frameTime_), elapsed(0.f), current(0)
{}

void Animation::addFrame(const BitmapHandler& bmp) {
    frames.push_back(bmp);
}

void Animation::update(float dt) {
    if (frames.empty()) return;
    elapsed += dt;
    if (elapsed >= frameTime) {
        elapsed -= frameTime;
        current = (current + 1) % frames.size();
    }
}

void Animation::draw(int x, int y, PrimitiveRenderer& renderer) const {
    // simple placeholder: draw a point for current frame center
    if (frames.empty()) return;
    renderer.drawCircle(x, y, 10, sf::Color::White, false);
}
