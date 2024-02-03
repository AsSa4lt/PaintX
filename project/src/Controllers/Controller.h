
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

enum class LineSize {
	SMALL,
	MEDIUM,
	LARGE
};

class Controller {
private:
	static Instrument instrument;
	static sf::Color color;
	static std::vector<Object*> objects;
	// current object
	static Object* currentObject;
	// gettter and setter for current object
	static LineSize lineSize;
	static bool isFilled;
public:
	static void setLineSize(LineSize lineSize);
	static float getLineSize();
	static void setCurrentObject(Object* object);
	static Object* getCurrentObject();
	static void AddObject(Object* object);
	static const std::vector<Object*> getObjects();
	static void setInstrument(Instrument instrument);
	static Instrument getInstrument();
	static void setColor(sf::Color color);
	static sf::Color getColor();
	static void setIsFilled(bool isFilled);
	static bool getIsFilled();
};