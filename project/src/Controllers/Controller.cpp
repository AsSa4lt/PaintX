// definition of static instrument and color
#include "Controller.h"

Instrument Controller::instrument = Instrument::LINE;
sf::Color Controller::color = sf::Color::Green;
std::vector<Object*> Controller::objects;
Object* Controller::currentObject = nullptr;
LineSize Controller::lineSize = LineSize::LARGE;


void Controller::setInstrument(Instrument instrument){
	Controller::instrument = instrument;
}

Instrument Controller::getInstrument(){
	return instrument;
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

