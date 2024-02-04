#pragma once
#include "Object.h"

class Rectangle : public Object {
public:
	// will implement method draw from Object
	void draw(sf::RenderWindow& window) override;
	// constructor, the same as Object
	Rectangle(sf::Vector2f start, sf::Vector2f end, sf::Color color, float width, bool isFilled) : Object(start, end, color, width, isFilled) {}
};