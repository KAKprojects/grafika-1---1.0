#pragma once
#include <vector>
#include "BitmapHandler.h"

class PrimitiveRenderer;

class Animation {
public:
    Animation(float frameTime = 0.1f);
    void addFrame(const BitmapHandler& bmp);
    void update(float dt);
    void draw(int x, int y, PrimitiveRenderer& renderer) const;

private:
    std::vector<BitmapHandler> frames;
    float frameTime;
    float elapsed;
    size_t current;
};
