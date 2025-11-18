#include "PrimitiveRenderer.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>

PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& w)
    : window(w), width(w.getSize().x), height(w.getSize().y)
{
    framebuffer.create(width, height, sf::Color::Black);
    texture.create(width, height);
    sprite.setTexture(texture);
}

void PrimitiveRenderer::clear(const sf::Color& col) {
    framebuffer.create(width, height, col);
}

// jeden piksel
void PrimitiveRenderer::setPixel(int x, int y, const sf::Color& col) {
    if (x >= 0 && x < (int)width && y >= 0 && y < (int)height)
        framebuffer.setPixel(x, y, col);
}

sf::Color PrimitiveRenderer::getPixel(int x, int y) const {
    if (x >= 0 && x < (int)width && y >= 0 && y < (int)height)
        return framebuffer.getPixel(x, y);
    return sf::Color::Transparent;
}

void PrimitiveRenderer::drawPoint(int x, int y, const sf::Color& col) { setPixel(x, y, col); }

void PrimitiveRenderer::drawCirclePoints(int cx, int cy, int x, int y, const sf::Color& col) {
    setPixel(cx + x, cy + y, col); setPixel(cx - x, cy + y, col);
    setPixel(cx + x, cy - y, col); setPixel(cx - x, cy - y, col);
    setPixel(cx + y, cy + x, col); setPixel(cx - y, cy + x, col);
    setPixel(cx + y, cy - x, col); setPixel(cx - y, cy - x, col);
}

void PrimitiveRenderer::drawCircle(int cx, int cy, int r, const sf::Color& col, bool ownAlgo) {
    if (!ownAlgo) {
        sf::CircleShape s((float)r);
        s.setPosition((float)(cx - r), (float)(cy - r));
        s.setFillColor(sf::Color::Transparent);
        s.setOutlineColor(col);
        s.setOutlineThickness(1.f);
        window.draw(s);
        return;
    }
    int x = 0, y = r, d = 3 - 2 * r;
    drawCirclePoints(cx, cy, x, y, col);
    while (y >= x) {
        x++;
        if (d > 0) { y--; d += 4 * (x - y) + 10; }
        else d += 4 * x + 6;
        drawCirclePoints(cx, cy, x, y, col);
    }
}

void PrimitiveRenderer::drawEllipse(int cx, int cy, int rx, int ry, const sf::Color& col, bool ownAlgo) {
    if (!ownAlgo) {
        sf::CircleShape s(1.f);
        s.setScale((float)rx, (float)ry);
        s.setPosition((float)(cx - rx), (float)(cy - ry));
        s.setFillColor(sf::Color::Transparent);
        s.setOutlineColor(col);
        s.setOutlineThickness(1.f);
        window.draw(s);
        return;
    }

    long a2 = (long)rx * rx;
    long b2 = (long)ry * ry;
    long x = 0;
    long y = ry;
    long fx = 0;
    long fy = 2 * a2 * ry;
    long p = b2 - a2 * ry + (a2 / 4);

    auto plot = [&](int px, int py) {
        setPixel(cx + px, cy + py, col);
        setPixel(cx - px, cy + py, col);
        setPixel(cx + px, cy - py, col);
        setPixel(cx - px, cy - py, col);
        };

    plot(x, y);

    while (fx < fy) {
        x++; fx += 2 * b2;
        if (p < 0) p += b2 + fx;
        else { y--; fy -= 2 * a2; p += b2 + fx - fy; }
        plot(x, y);
    }

    p = b2 * (x + 1) * (x + 1) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y > 0) {
        y--; fy -= 2 * a2;
        if (p > 0) p += a2 - fy;
        else { x++; fx += 2 * b2; p += a2 - fy + fx; }
        plot(x, y);
    }
}

void PrimitiveRenderer::drawLine(int x0, int y0, int x1, int y1, const sf::Color& col, bool incremental) {
    if (!incremental) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f((float)x0, (float)y0), col),
            sf::Vertex(sf::Vector2f((float)x1, (float)y1), col)
        };
        window.draw(line, 2, sf::Lines);
        return;
    }
    // algorytm Bresenhama
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    while (true) {
        setPixel(x0, y0, col);
        if (x0 == x1 && y0 == y1) 
            break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void PrimitiveRenderer::drawPolyline(const std::vector<Point2D>& points, const sf::Color& col, bool closed) {
    for (size_t i = 0; i + 1 < points.size(); ++i)
        drawLine(points[i].getX(), points[i].getY(), points[i + 1].getX(), points[i + 1].getY(), col, true);
    if (closed && points.size() >= 2)
        drawLine(points.back().getX(), points.back().getY(), points[0].getX(), points[0].getY(), col, true);
}

static bool segmentsIntersect(const Point2D& a, const Point2D& b, const Point2D& c, const Point2D& d) {
    auto orient = [](const Point2D& p, const Point2D& q, const Point2D& r) -> int {
        long long val = (long long)(q.getY() - p.getY()) * (r.getX() - q.getX()) -
            (long long)(q.getX() - p.getX()) * (r.getY() - q.getY());
        if (val == 0) 
            return 0;
        return val > 0 ? 1 : 2;
        };
    int o1 = orient(a, b, c), o2 = orient(a, b, d);
    int o3 = orient(c, d, a), o4 = orient(c, d, b);
    if (o1 != o2 && o3 != o4) 
        return true;
    return false;
}

void PrimitiveRenderer::drawPolygon(const std::vector<Point2D>& points, const sf::Color& col) {
    if (points.size() < 3) 
        return;
    for (size_t i = 0; i < points.size(); ++i) {
        Point2D a = points[i];
        Point2D b = points[(i + 1) % points.size()];
        for (size_t j = i + 2; j < points.size(); ++j) {
            Point2D c = points[j];
            Point2D d = points[(j + 1) % points.size()];
            if ((i + 1) % points.size() == j || (j + 1) % points.size() == i) continue;
            if (segmentsIntersect(a, b, c, d)) {
                std::cout << "Wielok¹t ma przeciêcia \n";
                return;
            }
        }
    }
    drawPolyline(points, col, true);
}

void PrimitiveRenderer::floodFill(int x, int y, const sf::Color& fillCol) {
    sf::Color old = getPixel(x, y);
    if (old == fillCol) return;
    std::queue<std::pair<int, int>> q;
    q.push({ x,y }); setPixel(x, y, fillCol);
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        if (getPixel(cx + 1, cy) == old) { setPixel(cx + 1, cy, fillCol); q.push({ cx + 1,cy }); }
        if (getPixel(cx - 1, cy) == old) { setPixel(cx - 1, cy, fillCol); q.push({ cx - 1,cy }); }
        if (getPixel(cx, cy + 1) == old) { setPixel(cx, cy + 1, fillCol); q.push({ cx,cy + 1 }); }
        if (getPixel(cx, cy - 1) == old) { setPixel(cx, cy - 1, fillCol); q.push({ cx,cy - 1 }); }
    }
}

void PrimitiveRenderer::boundaryFill(int x, int y, const sf::Color& fillCol, const sf::Color& borderCol) {
    if (getPixel(x, y) == fillCol || getPixel(x, y) == borderCol) 
        return;
    std::queue<std::pair<int, int>> q;
    q.push({ x,y }); setPixel(x, y, fillCol);
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        if (getPixel(cx + 1, cy) != fillCol && getPixel(cx + 1, cy) != borderCol) { setPixel(cx + 1, cy, fillCol); q.push({ cx + 1,cy }); }
        if (getPixel(cx - 1, cy) != fillCol && getPixel(cx - 1, cy) != borderCol) { setPixel(cx - 1, cy, fillCol); q.push({ cx - 1,cy }); }
        if (getPixel(cx, cy + 1) != fillCol && getPixel(cx, cy + 1) != borderCol) { setPixel(cx, cy + 1, fillCol); q.push({ cx,cy + 1 }); }
        if (getPixel(cx, cy - 1) != fillCol && getPixel(cx, cy - 1) != borderCol) { setPixel(cx, cy - 1, fillCol); q.push({ cx,cy - 1 }); }
    }
}

void PrimitiveRenderer::drawFilledCircle(int cx, int cy, int r, const sf::Color& col) {
    int x = 0, y = r, d = 3 - 2 * r;
    while (y >= x) {
        for (int i = cx - x; i <= cx + x; i++) { setPixel(i, cy + y, col); setPixel(i, cy - y, col); }
        for (int i = cx - y; i <= cx + y; i++) { setPixel(i, cy + x, col); setPixel(i, cy - x, col); }
        x++;
        if (d > 0) { y--; d += 4 * (x - y) + 10; }
        else d += 4 * x + 6;
    }
}

void PrimitiveRenderer::flush() {
    texture.update(framebuffer);
    window.draw(sprite);
}