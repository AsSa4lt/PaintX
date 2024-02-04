#include "Ellipse.h"

void Ellipse::draw(sf::RenderWindow& window) {
    // Calculate actual size based on current window size
    sf::Vector2f size((end.x - start.x) * window.getSize().x, (end.y - start.y) * window.getSize().y);

    // Calculate the center of the ellipse
    sf::Vector2f center(start.x * window.getSize().x + size.x / 2.0f, start.y * window.getSize().y + size.y / 2.0f);

    // Number of points for the ellipse
    const int points = 100; // More points for a smoother ellipse
    const float angleStep = 2 * M_PI / points;

    // Set up the vertices for the outline
    std::vector<sf::Vertex> outlineVertices;

    float realWidth = width * 3;
    for (int i = 0; i < points; ++i) {
        // Angle for this segment
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        // Outer edge of this segment
        sf::Vector2f pointOuter(cos(angle) * size.x / 2.0f, sin(angle) * size.y / 2.0f);
        sf::Vector2f nextPointOuter(cos(nextAngle) * size.x / 2.0f, sin(nextAngle) * size.y / 2.0f);

        // Inner edge of this segment
        sf::Vector2f pointInner(cos(angle) * (size.x - realWidth) / 2.0f, sin(angle) * (size.y - realWidth) / 2.0f);
        sf::Vector2f nextPointInner(cos(nextAngle) * (size.x - realWidth) / 2.0f, sin(nextAngle) * (size.y - realWidth) / 2.0f);

        // Add the vertices for the quad (two triangles) making up this segment
        outlineVertices.push_back(sf::Vertex(center + pointOuter, color));
        outlineVertices.push_back(sf::Vertex(center + nextPointOuter, color));
        outlineVertices.push_back(sf::Vertex(center + nextPointInner, color));
        outlineVertices.push_back(sf::Vertex(center + pointInner, color));
    }

    // If the ellipse is filled, draw the filled ellipse underneath the outline
    if (isFilled) {
        sf::ConvexShape filledEllipse;
        filledEllipse.setPointCount(points);
        for (int i = 0; i < points; ++i) {
            float angle = i * angleStep;
            sf::Vector2f pointOuter(cos(angle) * size.x / 2.0f, sin(angle) * size.y / 2.0f);
            filledEllipse.setPoint(i, center + pointOuter);
        }
        filledEllipse.setFillColor(color);
        window.draw(filledEllipse);
    }

    // Now draw the outline
    window.draw(&outlineVertices[0], outlineVertices.size(), sf::Quads);
}

bool Ellipse::isInside(sf::Vector2f point, sf::RenderWindow& window) {
    // Calculate the center of the ellipse
    sf::Vector2f center(start.x * window.getSize().x + (end.x - start.x) * window.getSize().x / 2.0f,
        start.y * window.getSize().y + (end.y - start.y) * window.getSize().y / 2.0f);

    // Calculate the radii of the ellipse
    float a = (end.x - start.x) * window.getSize().x / 2.0f; // Horizontal radius
    float b = (end.y - start.y) * window.getSize().y / 2.0f; // Vertical radius

    // Adjust the point's coordinates to be relative to the ellipse's center
    sf::Vector2f relativePoint = point - center;

    if (isFilled) {
        // For a filled ellipse, check if the point is within the ellipse bounds
        return (relativePoint.x * relativePoint.x) / (a * a) + (relativePoint.y * relativePoint.y) / (b * b) <= 1;
    }
    else {
        // For an outlined ellipse, calculate outer and inner radii based on the outline width
        float realWidth = width; // The actual outline width of the ellipse
        float aOuter = a + realWidth / 2.0f;
        float bOuter = b + realWidth / 2.0f;
        float aInner = std::max(0.0f, a - realWidth / 2.0f); // Ensure inner radii are not negative
        float bInner = std::max(0.0f, b - realWidth / 2.0f);

        // Check if the point is within the outer ellipse
        bool withinOuter = (relativePoint.x * relativePoint.x) / (aOuter * aOuter) + (relativePoint.y * relativePoint.y) / (bOuter * bOuter) <= 1;
        // Check if the point is outside the inner ellipse
        bool outsideInner = (relativePoint.x * relativePoint.x) / (aInner * aInner) + (relativePoint.y * relativePoint.y) / (bInner * bInner) >= 1;

        // The point is considered near the outline if it's within the outer ellipse and outside the inner ellipse
        return withinOuter && outsideInner;
    }
}

std::string Ellipse::getType(){
    return "Ellipse";
}

