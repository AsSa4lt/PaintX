#include "Line.h"

void Line::draw(sf::RenderWindow& window){
	// draw the line from the start to the end by using percentage of the screen x1, y1, x2, y2;
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(start.x * window.getSize().x, start.y * window.getSize().y)),
		sf::Vertex(sf::Vector2f(end.x * window.getSize().x, end.y * window.getSize().y))
	};
	window.draw(line, 2, sf::Lines);
}
