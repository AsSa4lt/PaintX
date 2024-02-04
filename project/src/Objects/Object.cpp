#include "Object.h"

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
