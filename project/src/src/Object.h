#pragma once
/*
Object
have color inside
have position inside
have size inside
have rotation inside(maybe in future)
will be rendered by sfml
*/
#include <SFML/Graphics.hpp>
class Object
{
public:
	Object();
	~Object();
	// properties
	sf::Color color;
	sf::Vector2f position;
	sf::Vector2f size;
	// methods
	void draw(sf::RenderWindow& window);


};

