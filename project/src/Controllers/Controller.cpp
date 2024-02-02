// definition of static instrument and color
#include "Controller.h"

Instrument Controller::instrument = Instrument::LINE;
sf::Color Controller::color = sf::Color::Green;
std::vector<Object*> Controller::objects;
Object* Controller::currentObject = nullptr;


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

