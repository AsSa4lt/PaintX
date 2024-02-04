// definition of static instrument and color
#include "Controller.h"

Shapes Controller::shape = Shapes::TRIANGLE;
sf::Color Controller::color = sf::Color::Green;
std::vector<Object*> Controller::objects;
Object* Controller::currentObject = nullptr;
LineSize Controller::lineSize = LineSize::LARGE;
bool Controller::isFilled = false;
Instrument Controller::instrument = Instrument::NONE;


void Controller::setShape(Shapes shape){
	Controller::shape = shape;
	instrument = Instrument::NONE;
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

