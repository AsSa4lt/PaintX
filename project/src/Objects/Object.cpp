#include "Object.h"

void Object::setEnd(sf::Vector2f end){
	this->end = end;
}

sf::Color Object::getColor(){
     return color;
}

sf::Vector2f Object::getStart(){
	 return start;
}

sf::Vector2f Object::getEnd(){
	 return end;
}

float Object::getLineWidth(){
	 return width;
}

bool Object::getFilled(){
	 return isFilled;
}

void Object::resize(sf::Vector2f offset){
	end += offset;
}

void Object::move(sf::Vector2f offset){
	end += offset;
	start += offset;
}
