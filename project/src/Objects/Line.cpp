#include "Line.h"
#include <SFML/Graphics.hpp>
#include <cmath> // For std::sqrt, std::atan2

void Line::draw(sf::RenderWindow& window) {
    // Calculate actual start and end positions based on current window size
    sf::Vector2f actualStart(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f actualEnd(end.x * window.getSize().x, end.y * window.getSize().y);

    // Direction vector from start to end
    sf::Vector2f direction = actualEnd - actualStart;
    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0) return; // Prevent division by zero if start and end are the same
    sf::Vector2f unitDirection = direction / length;
    // Calculate the perpendicular vector to the direction vector
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);
    // Scale the perpendicular vector by half the line width to get the offset from the center
    sf::Vector2f offset = unitPerpendicular * (width / 2.0f);

    // Calculate the vertices of the rectangle (the thick line)
    sf::Vertex vertices[4];
    vertices[0].position = actualStart - offset;
    vertices[1].position = actualStart + offset;
    vertices[2].position = actualEnd - offset;
    vertices[3].position = actualEnd + offset;

    // Set the color of the line
    for (int i = 0; i < 4; ++i) {
        vertices[i].color = color; 
    }

    // Draw the thick line
    window.draw(vertices, 4, sf::TriangleStrip);
}

bool Line::isInside(sf::Vector2f point, sf::RenderWindow& window)
{
    // Calculate actual start and end positions based on current window size
    sf::Vector2f actualStart(start.x * window.getSize().x, start.y * window.getSize().y);
    sf::Vector2f actualEnd(end.x * window.getSize().x, end.y * window.getSize().y);

    // Calculate the vectors from the endpoints of the line to the point
    sf::Vector2f toPointStart = point - actualStart;
    sf::Vector2f toPointEnd = point - actualEnd;

    // Calculate the dot product of the vectors
    float dotProduct = toPointStart.x * toPointEnd.x + toPointStart.y * toPointEnd.y;

    // If the dot product is greater than zero, the point is outside the line segment
    if (dotProduct > 0) {
        return false;
    }

    // Compute the distance from the point to the line segment
    float lineLengthSquared = (actualEnd - actualStart).x * (actualEnd - actualStart).x +
        (actualEnd - actualStart).y * (actualEnd - actualStart).y;
    float t = ((point - actualStart).x * (actualEnd - actualStart).x +
        (point - actualStart).y * (actualEnd - actualStart).y) /
        lineLengthSquared;

    if (t < 0.0f || t > 1.0f) {
        return false; // The projection is outside the segment
    }

    sf::Vector2f projection = actualStart + (actualEnd - actualStart) * t;
    float distanceSquared = (point - projection).x * (point - projection).x +
        (point - projection).y * (point - projection).y;

    // If the distance from the point to the line is less than the width, it's "inside"
    return distanceSquared <= (width / 2.0f) * (width / 2.0f);
}

std::string Line::getType(){
	return "Line";
}
