// definition of static instrument and color
#include "Controller.h"

Instrument Controller::instrument = Instrument::NONE;
sf::Color Controller::color = sf::Color::Black;
Window* Controller::window = nullptr;

void Controller::setWindow(Window* window){
	Controller::window = window;
}

Window* Controller::getWindow(){
	return window;
}

void Controller::setInstrument(Instrument instrument){
	Controller::instrument = instrument;
}

Instrument Controller::getInstrument(){
	return instrument;
}
