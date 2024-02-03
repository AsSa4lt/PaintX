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
