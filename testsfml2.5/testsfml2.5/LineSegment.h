#pragma once
#include "Point2D.h"

class PrimitiveRenderer;

class LineSegment {
    Point2D start, end; // pocz¹tek i koniec odcinka
public:
    LineSegment(const Point2D& a = Point2D(), const Point2D& b = Point2D()) : start(a), end(b) {}
    const Point2D& getStart() const { 
        return start; 
    }
    const Point2D& getEnd()   const { 
        return end; 
    }
    void draw(PrimitiveRenderer& pr, const sf::Color& c = sf::Color::White, bool incremental = true) const; // rysujê liniê
};