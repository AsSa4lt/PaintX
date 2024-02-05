
#pragma once
/*static class for storing intsrument and colors*/
#include <SFML/Graphics.hpp>
#include "Objects/Object.h"

enum class Shapes {
	NONE,
	LINE,
	RECTANGLE,
	ELLIPSE,
	TRIANGLE,
};

enum class Tool {
	NONE,
	ERASER,
	RESIZE,
	MOVE
};

enum class LineSize {
	NONE,
	SMALL,
	MEDIUM,
	LARGE
};

class Controller {
private:
	static Shapes shape;
	static sf::Color color;
	static std::vector<Object*> objects;
	static Tool instrument;
	// current object
	static Object* currentObject;
	static Object* movingObject;
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
	static void setShape(Shapes instrument);
	static Shapes getShape();
	static void setColor(sf::Color color);
	static sf::Color getColor();
	static void setIsFilled(bool isFilled);
	static bool getIsFilled();
	static LineSize getLineSizeParameter();
	static void setTool(Tool tool);
	static Tool getTool();
	static void RemoveObject(Object* object);
	static void ClearObjects();
	static void setMovingObject(Object* object);
	static Object* getMovingObject();
	static void ClearController();
};