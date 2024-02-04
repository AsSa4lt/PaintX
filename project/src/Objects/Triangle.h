#pragma once
#include "Object.h"

class Triangle : public Object{
public:
	// will implement method draw from Object
    void draw(sf::RenderWindow& window) override;

    // Helper function to draw a thick line using a rectangle
	void drawThickLine(sf::RenderWindow& window, sf::Vertex start, sf::Vertex end, float thickness, sf::Color color);
	// constructor, the same as Object
	Triangle(sf::Vector2f start, sf::Vector2f end, sf::Color color, float width, bool isFilled) : Object(start, end, color, width, isFilled) { }
	
	bool isInside(sf::Vector2f point, sf::RenderWindow& window) override;
	
	std::string getType() override;
};