#include "LineSegment.h"
#include "PrimitiveRenderer.h"

void LineSegment::draw(PrimitiveRenderer& pr, const sf::Color& c, bool incremental) const {
    pr.drawLine(start.getX(), start.getY(), end.getX(), end.getY(), c, incremental);
}