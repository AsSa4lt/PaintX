
#pragma once
#include "Objects/Object.h"
#include "Objects/Line.h"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"

/* static class taht will get current instrument and color from Controller
   start and end point by parameters

*/
class ObjectsFactory{
public:
	static Object* createObject(const sf::Vector2f& start, const sf::Vector2f& end) {
		if (Controller::getInstrument() == Instrument::LINE) {
			// create a line
			return new Line(start, end, Controller::color, Controller::getLineSize());
		}
		return nullptr;
	}
};