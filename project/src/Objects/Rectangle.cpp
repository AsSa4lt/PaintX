#include "Rectangle.h"

void Rectangle::draw(sf::RenderWindow& window) {
    // Calculate actual corner positions based on current window size
    sf::Vector2f actualTopLeft(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f actualBottomRight(end.x * window.getSize().x, end.y * window.getSize().y);

    // Calculate the other two corners based on actualTopLeft and actualBottomRight
    sf::Vector2f actualTopRight(actualBottomRight.x, actualTopLeft.y);
    sf::Vector2f actualBottomLeft(actualTopLeft.x, actualBottomRight.y);

    // Line thickness for offset calculation
    float halfWidth = width / 2.0f;

    if (isFilled) {
        // Create and draw a filled rectangle
        sf::RectangleShape rectangle(actualBottomRight - actualTopLeft);
        rectangle.setPosition(actualTopLeft);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    }
    else {
        // Draw the outline by extending the sides to overlap at the corners
        sf::Vertex vertices[] = {
            // Top side
            sf::Vertex(actualTopLeft + sf::Vector2f(-halfWidth, halfWidth), color),
            sf::Vertex(actualTopRight + sf::Vector2f(halfWidth, halfWidth), color),
            sf::Vertex(actualTopRight + sf::Vector2f(halfWidth, -halfWidth), color),
            sf::Vertex(actualTopLeft + sf::Vector2f(-halfWidth, -halfWidth), color),
            // Right side
            sf::Vertex(actualTopRight + sf::Vector2f(-halfWidth, -halfWidth), color),
            sf::Vertex(actualBottomRight + sf::Vector2f(-halfWidth, halfWidth), color),
            sf::Vertex(actualBottomRight + sf::Vector2f(halfWidth, halfWidth), color),
            sf::Vertex(actualTopRight + sf::Vector2f(halfWidth, -halfWidth), color),
            // Bottom side
            sf::Vertex(actualBottomRight + sf::Vector2f(halfWidth, -halfWidth), color),
            sf::Vertex(actualBottomLeft + sf::Vector2f(-halfWidth, -halfWidth), color),
            sf::Vertex(actualBottomLeft + sf::Vector2f(-halfWidth, halfWidth), color),
            sf::Vertex(actualBottomRight + sf::Vector2f(halfWidth, halfWidth), color),
            // Left side
            sf::Vertex(actualBottomLeft + sf::Vector2f(-halfWidth, halfWidth), color),
            sf::Vertex(actualTopLeft + sf::Vector2f(-halfWidth, -halfWidth), color),
            sf::Vertex(actualTopLeft + sf::Vector2f(halfWidth, -halfWidth), color),
            sf::Vertex(actualBottomLeft + sf::Vector2f(halfWidth, halfWidth), color)
        };

        // Draw the thick lines for the rectangle
        window.draw(vertices, 4, sf::Quads); // Top side
        window.draw(vertices + 4, 4, sf::Quads); // Right side
        window.draw(vertices + 8, 4, sf::Quads); // Bottom side
        window.draw(vertices + 12, 4, sf::Quads); // Left side
    }
}

