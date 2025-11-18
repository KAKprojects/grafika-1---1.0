#include "Point2D.h"
#include "PrimitiveRenderer.h"

void Point2D::draw(PrimitiveRenderer& pr, const sf::Color& color) const {
    pr.drawPoint(x, y, color);
}