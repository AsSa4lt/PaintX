#include "Triangle.h"
#include <array>

void Triangle::draw(sf::RenderWindow& window) {
    // Calculate actual corner positions based on current window size
    sf::Vector2f firstCorner(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f secondCorner(end.x * window.getSize().x, end.y * window.getSize().y);
    // The third point makes it a right-angled triangle
    sf::Vector2f thirdCorner(end.x * window.getSize().x, start.y * window.getSize().y);

    if (isFilled) {
        // Create and draw a filled triangle
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, firstCorner);
        triangle.setPoint(1, secondCorner);
        triangle.setPoint(2, thirdCorner);
        triangle.setFillColor(color);
        window.draw(triangle);
    }
    else {
        // Draw the outline of the triangle with a specified width
        sf::Vertex line1[] = {
            sf::Vertex(firstCorner, color),
            sf::Vertex(secondCorner, color)
        };

        sf::Vertex line2[] = {
            sf::Vertex(secondCorner, color),
            sf::Vertex(thirdCorner, color)
        };

        sf::Vertex line3[] = {
            sf::Vertex(thirdCorner, color),
            sf::Vertex(firstCorner, color)
        };

        // Since SFML doesn't support line thickness for lines, we use rectangles to simulate the thick lines
        drawThickLine(window, line1[0], line1[1], width, color);
        drawThickLine(window, line2[0], line2[1], width, color);
        drawThickLine(window, line3[0], line3[1], width, color);
    }
}


// Helper function to draw a thick line using a rectangle
void Triangle::drawThickLine(sf::RenderWindow& window, sf::Vertex start, sf::Vertex end, float thickness, sf::Color color) {
    sf::Vector2f direction = end.position - start.position;
    sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    // Extend the lines slightly at the corners
    float extensionLength = thickness / 2.f;
    sf::Vector2f extension = unitDirection * extensionLength;

    sf::ConvexShape thickLine;
    thickLine.setPointCount(4);
    thickLine.setPoint(0, start.position + offset - extension);
    thickLine.setPoint(1, start.position - offset - extension);
    thickLine.setPoint(2, end.position - offset + extension);
    thickLine.setPoint(3, end.position + offset + extension);
    thickLine.setFillColor(color);

    window.draw(thickLine);
}
float dot(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

float length(sf::Vector2f v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

bool Triangle::isInside(sf::Vector2f point, sf::RenderWindow& window) {
    // Calculate actual corner positions based on current window size
    sf::Vector2f firstCorner(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f secondCorner(end.x * window.getSize().x, end.y * window.getSize().y);
    sf::Vector2f thirdCorner(end.x * window.getSize().x, start.y * window.getSize().y);

    // Helper lambda to calculate the sign of a determinant
    auto sign = [](sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        };

    bool b1, b2, b3;

    b1 = sign(point, firstCorner, secondCorner) < 0.0f;
    b2 = sign(point, secondCorner, thirdCorner) < 0.0f;
    b3 = sign(point, thirdCorner, firstCorner) < 0.0f;

    if (isFilled) {
        // If the triangle is filled, we just need to check if the point is inside the triangle
        return ((b1 == b2) && (b2 == b3));
    }
    else {
        // If the triangle is not filled, we need to check if the point is near any of the edges
        float lineThickness = width; // Width is assumed to be the line thickness for the triangle's outline
        auto checkLine = [lineThickness](sf::Vector2f p, sf::Vector2f a, sf::Vector2f b) {
            sf::Vector2f pa = p - a, ba = b - a;
            float h = std::clamp(dot(pa, ba) / dot(ba, ba), 0.0f, 1.0f);
            return length(pa - ba * h) < lineThickness;
            };
        return checkLine(point, firstCorner, secondCorner) ||
            checkLine(point, secondCorner, thirdCorner) ||
            checkLine(point, thirdCorner, firstCorner);
    }
}
