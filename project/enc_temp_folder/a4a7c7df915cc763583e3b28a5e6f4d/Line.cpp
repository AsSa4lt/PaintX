#include "Line.h"

void Line::draw(sf::RenderWindow& window){
	// draw the line from the start to the end
	sf::Vertex line[] = {
		sf::Vertex(start, color),
		sf::Vertex(end, color)
	};
	window.draw(line, 2, sf::Lines);
}
