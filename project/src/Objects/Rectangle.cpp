#include "Rectangle.h"

void Rectangle::draw(sf::RenderWindow& window) {
    // Calculate actual corner positions based on current window size
    sf::Vector2f actualTopLeft(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f actualBottomRight(end.x * window.getSize().x, end.y * window.getSize().y);

    // Calculate the other two corners based on actualTopLeft and actualBottomRight
    sf::Vector2f actualTopRight(actualBottomRight.x, actualTopLeft.y);
    sf::Vector2f actualBottomLeft(actualTopLeft.x, actualBottomRight.y);

    // Line thickness for offset calculation
    float RealWidth = width / 2.0f;

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
            sf::Vertex(actualTopLeft + sf::Vector2f(-RealWidth, RealWidth), color),
            sf::Vertex(actualTopRight + sf::Vector2f(RealWidth, RealWidth), color),
            sf::Vertex(actualTopRight + sf::Vector2f(RealWidth, -RealWidth), color),
            sf::Vertex(actualTopLeft + sf::Vector2f(-RealWidth, -RealWidth), color),
            // Right side
            sf::Vertex(actualTopRight + sf::Vector2f(-RealWidth, -RealWidth), color),
            sf::Vertex(actualBottomRight + sf::Vector2f(-RealWidth, RealWidth), color),
            sf::Vertex(actualBottomRight + sf::Vector2f(RealWidth, RealWidth), color),
            sf::Vertex(actualTopRight + sf::Vector2f(RealWidth, -RealWidth), color),
            // Bottom side
            sf::Vertex(actualBottomRight + sf::Vector2f(RealWidth, -RealWidth), color),
            sf::Vertex(actualBottomLeft + sf::Vector2f(-RealWidth, -RealWidth), color),
            sf::Vertex(actualBottomLeft + sf::Vector2f(-RealWidth, RealWidth), color),
            sf::Vertex(actualBottomRight + sf::Vector2f(RealWidth, RealWidth), color),
            // Left side
            sf::Vertex(actualBottomLeft + sf::Vector2f(-RealWidth, RealWidth), color),
            sf::Vertex(actualTopLeft + sf::Vector2f(-RealWidth, -RealWidth), color),
            sf::Vertex(actualTopLeft + sf::Vector2f(RealWidth, -RealWidth), color),
            sf::Vertex(actualBottomLeft + sf::Vector2f(RealWidth, RealWidth), color)
        };

        // Draw the thick lines for the rectangle
        window.draw(vertices, 4, sf::Quads); // Top side
        window.draw(vertices + 4, 4, sf::Quads); // Right side
        window.draw(vertices + 8, 4, sf::Quads); // Bottom side
        window.draw(vertices + 12, 4, sf::Quads); // Left side
    }
}

bool Rectangle::isInside(sf::Vector2f point, sf::RenderWindow& window)
{
    // Calculate actual corner positions based on current window size
    sf::Vector2f actualTopLeft(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f actualBottomRight(end.x * window.getSize().x, end.y * window.getSize().y);

    if (isFilled) {
        // For a filled rectangle, we check if the point is within the rectangle bounds
        return (point.x >= actualTopLeft.x && point.x <= actualBottomRight.x &&
            point.y >= actualTopLeft.y && point.y <= actualBottomRight.y);
    }
    else {
        // For an unfilled rectangle, we check if the point is near any of the four sides
        float halfWidth = width / 2.0f;

        // Define the four sides as lines
        sf::FloatRect top(actualTopLeft.x - halfWidth, actualTopLeft.y - halfWidth, actualBottomRight.x - actualTopLeft.x + width, width);
        sf::FloatRect bottom(actualTopLeft.x - halfWidth, actualBottomRight.y - halfWidth, actualBottomRight.x - actualTopLeft.x + width, width);
        sf::FloatRect left(actualTopLeft.x - halfWidth, actualTopLeft.y - halfWidth, width, actualBottomRight.y - actualTopLeft.y + width);
        sf::FloatRect right(actualBottomRight.x - halfWidth, actualTopLeft.y - halfWidth, width, actualBottomRight.y - actualTopLeft.y + width);

        // Check if the point is inside any of the four sides
        return top.contains(point) || bottom.contains(point) || left.contains(point) || right.contains(point);
    }
}

std::string Rectangle::getType(){
    return "Rectangle";
}

