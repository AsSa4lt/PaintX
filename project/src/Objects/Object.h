/* 
Class that will be used for derived classs of shapes
Lines, ellipses, rectangles, triangles.
*/
#pragma once
#include "SFML/Graphics.hpp"
class Object {
protected:
	// will have it start position and end position, it should use percentage of the screen, use vector2f
	sf::Vector2f start;
	sf::Vector2f end;
	// color of the object
	sf::Color color;
	// width of line
	float width;
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	// constructor
	Object(sf::Vector2f start, sf::Vector2f end, sf::Color color, float width) {
		this->start = start;
		this->end = end;
		this->color = color;
		this->width = width;
	}
	// update the end position
	void setEnd(sf::Vector2f end) {
		this->end = end;
	}
};		