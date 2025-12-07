#pragma once
#include "PrimitiveRenderer.h"
#include "UpdatableObject.h"
#include "DrawableObject.h"

class DemoScene {
public:
    DemoScene(PrimitiveRenderer& r);
    void init();
    void update(float dt);
    void render();
private:
    PrimitiveRenderer& renderer;
    float t = 0.f;
};
