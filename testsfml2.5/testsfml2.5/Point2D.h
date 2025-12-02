#pragma once
#include <SFML/Graphics.hpp>

class PrimitiveRenderer;

class Point2D {
private:
    int x, y;
public:
    Point2D(int x = 0, int y = 0) : x(x), y(y) {}
    int getX() const { 
      return x; 
      }
    int getY() const { 
      return y; 
      }
    void setX(int v) { x = v; 
      }
    void setY(int v) { y = v; 
      }
    void draw(PrimitiveRenderer& pr, const sf::Color& color = sf::Color::White) const;
};