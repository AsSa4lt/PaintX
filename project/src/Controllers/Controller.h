
#pragma once
/*static class for storing intsrument and colors*/
#include <SFML/Graphics.hpp>
#include "Objects/Object.h"

enum class Instrument {
	NONE,
	PENCIL,
	ERASER,
	LINE,
	RECTANGLE,
	ELLIPS,
	TRIANGLE,
	SELECT
};

class Controller {
public:
	static Instrument instrument;
	static sf::Color color;
	static void setInstrument(Instrument instrument);
	static Instrument getInstrument();
	static std::vector<Object*> objects;
	static void AddObject(Object* object);
	static const std::vector<Object*> getObjects();
	// current object
	static Object* currentObject;
	// gettter and setter for current object
	static void setCurrentObject(Object* object);
	static Object* getCurrentObject();
};