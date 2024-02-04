#pragma once
#include "Object.h"

class Ellipse : public Object {
	const float M_PI = 3.14159265f;
public:
	// will implement method draw from Object
	void draw(sf::RenderWindow& window) override;
	// constructor, the same as Object
	Ellipse(sf::Vector2f start, sf::Vector2f end, sf::Color color, float width, bool isFilled) : Object(start, end, color, width, isFilled) {};
	bool isInside(sf::Vector2f point, sf::RenderWindow& window) override;
	std::string getType() override;
};