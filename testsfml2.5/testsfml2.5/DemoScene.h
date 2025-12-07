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
    void handleKeyPress(int key);
    
private:
    PrimitiveRenderer& renderer;
    float t = 0.f;
    int mode = 1;  // Current demo mode (1-6)
    
    // Helper methods for each mode
    void renderModeGeometry();       // Mode 1: Basic geometry
    void renderModeAnimated();       // Mode 2: Animated shapes
    void renderModeFilled();         // Mode 3: Filled shapes with colors
    void renderModePolygons();       // Mode 4: Complex polygons
    void renderModeTransform();      // Mode 5: Transformations
    void renderModeInteractive();    // Mode 6: Interactive mode
};
