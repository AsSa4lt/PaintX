/* 
Class that will be used for derived classs of shapes
Lines, ellipses, rectangles, triangles.
*/
#include "SFML/Graphics.hpp";
class Object {
protected:
	// will have it start position and end position
	sf::Vector2f start;
	sf::Vector2f end;
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};