#include "Line.h"
#include <cmath>
void Line::draw(sf::RenderWindow& window){

	// use TriangleStrip to use width
     // Calculate the direction vector of the line
    sf::Vector2f direction = sf::Vector2f(end.x * window.getSize().x, end.y * window.getSize().y) - sf::Vector2f(start.x * window.getSize().x, start.y * window.getSize().y);
    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitDirection = direction / length;
    // Calculate the perpendicular vector to the direction vector
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);
    // Scale the perpendicular vector by half the line width to get the offset from the center
    sf::Vector2f offset = unitPerpendicular * (width / 2.0f);

    // Calculate the vertices of the rectangle (the thick line)
    sf::Vertex vertices[4];
    vertices[0].position = sf::Vector2f(start.x * window.getSize().x, start.y * window.getSize().y) - offset;
    vertices[1].position = sf::Vector2f(start.x * window.getSize().x, start.y * window.getSize().y) + offset;
    vertices[2].position = sf::Vector2f(end.x * window.getSize().x, end.y * window.getSize().y) - offset;
    vertices[3].position = sf::Vector2f(end.x * window.getSize().x, end.y * window.getSize().y) + offset;

    // Set the color of the line
    for (int i = 0; i < 4; ++i) {
        vertices[i].color = color; // Assuming 'color' is a class member of type sf::Color
    }

    // Draw the thick line
    window.draw(vertices, 4, sf::TriangleStrip);
}
