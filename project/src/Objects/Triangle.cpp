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