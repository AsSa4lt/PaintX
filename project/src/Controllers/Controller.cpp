// definition of static instrument and color
#include "Controller.h"

Shapes Controller::shape = Shapes::TRIANGLE;
sf::Color Controller::color = sf::Color::Green;
std::vector<Object*> Controller::objects;
Object* Controller::currentObject = nullptr;
LineSize Controller::lineSize = LineSize::LARGE;
bool Controller::isFilled = false;
Tool Controller::instrument = Tool::NONE;


void Controller::setShape(Shapes shape){
	Controller::shape = shape;
	instrument = Tool::NONE;
}

Shapes Controller::getShape(){
	return shape;
}

void Controller::AddObject(Object* object){
	objects.push_back(object);
}

const std::vector<Object*> Controller::getObjects(){
	return objects;
}

void Controller::setCurrentObject(Object* object){
	currentObject = object;
}

Object* Controller::getCurrentObject(){
	return currentObject;
}

void Controller::setLineSize(LineSize lineSize){
	Controller::lineSize = lineSize;
}

sf::Color Controller::getColor(){
	return color;
}

void Controller::setColor(sf::Color color){
	Controller::color = color;
}

void Controller::setIsFilled(bool isFilled){
	Controller::isFilled = isFilled;
}

bool Controller::getIsFilled(){
	return isFilled;
}

LineSize Controller::getLineSizeParameter(){
	return lineSize;
}

void Controller::setTool(Tool instrument){
	Controller::instrument = instrument;
	Controller::shape = Shapes::NONE;
}

Tool Controller::getTool(){
	return instrument;
}

void Controller::RemoveObject(Object* object){
	// Use std::remove to shift the elements to be erased to the end, then erase them
	auto newEnd = std::remove(objects.begin(), objects.end(), object);

	// Actually erase the element(s) from the vector
	objects.erase(newEnd, objects.end());

	// Optionally, if you need to delete the object as well (assuming dynamic allocation)
	delete object;
}

void Controller::ClearObjects(){
	for (auto object : objects){
		delete object;
	}
	objects.clear();
}


float Controller::getLineSize() {
	switch (lineSize) {
	case LineSize::SMALL:
		return 1;
	case LineSize::MEDIUM:
		return 3;
	case LineSize::LARGE:
		return 5;
	}
	return 3;
}

