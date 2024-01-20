/* 
Class that will be used for derived classs of shapes
Lines, ellipses, rectangles, triangles.
*/
#include "SFML/Graphics.hpp";
class Object {
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};