#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"

class PrimitiveRenderer {
    sf::RenderWindow& window; // mogê rysowaæ
    sf::Image   framebuffer;
    sf::Texture texture;
    sf::Sprite  sprite;
    unsigned int width, height;

    void drawCirclePoints(int cx, int cy, int x, int y, const sf::Color& col);

public:
    PrimitiveRenderer(sf::RenderWindow& w);

    void clear(const sf::Color& col = sf::Color::Black);
    void setPixel(int x, int y, const sf::Color& col); // ustawiam kolor piksela
    sf::Color getPixel(int x, int y) const; // odczytuje kolor

    void drawPoint(int x, int y, const sf::Color& col = sf::Color::White);
    void drawLine(int x0, int y0, int x1, int y1, const sf::Color& col = sf::Color::White, bool incremental = true);
    void drawCircle(int cx, int cy, int r, const sf::Color& col = sf::Color::White, bool ownAlgo = true);
    void drawEllipse(int cx, int cy, int rx, int ry, const sf::Color& col = sf::Color::White, bool ownAlgo = true);
    void drawPolyline(const std::vector<Point2D>& points, const sf::Color& col = sf::Color::White, bool closed = false);
    void drawPolygon(const std::vector<Point2D>& points, const sf::Color& col = sf::Color::White); // punkty siê maj¹ nie przecinaæ

    void floodFill(int x, int y, const sf::Color& fillCol);
    void boundaryFill(int x, int y, const sf::Color& fillCol, const sf::Color& borderCol);
    void drawFilledCircle(int cx, int cy, int r, const sf::Color& col = sf::Color::White);

    void flush(); // pokazanie na ekranie
};