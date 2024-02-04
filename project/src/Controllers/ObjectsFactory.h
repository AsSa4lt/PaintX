
#pragma once
#include "Objects/Object.h"
#include "Objects/Line.h"
#include "Objects/Rectangle.h"
#include "Objects/Triangle.h"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"
#include "Objects/Ellipse.h"

/* static class taht will get current instrument and color from Controller
   start and end point by parameters

*/
class ObjectsFactory{
public:
	static Object* createObject(const sf::Vector2f& start, const sf::Vector2f& end) {
		if (Controller::getShape() == Shapes::LINE) {
			// create a line
			return new Line(start, end, Controller::getColor(), Controller::getLineSize(), Controller::getIsFilled());
		}
		else if (Controller::getShape() == Shapes::RECTANGLE) {
			return new Rectangle(start, end, Controller::getColor(), Controller::getLineSize(), Controller::getIsFilled());
		}
		else if (Controller::getShape() == Shapes::ELLIPSE) {
			return new Ellipse(start, end, Controller::getColor(), Controller::getLineSize(), Controller::getIsFilled());
		}
		else if (Controller::getShape() == Shapes::TRIANGLE) {
			return new Triangle(start, end, Controller::getColor(), Controller::getLineSize(), Controller::getIsFilled());
		}
		return nullptr;
	}
};