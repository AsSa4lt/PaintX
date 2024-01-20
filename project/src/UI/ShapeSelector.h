/* Selector of shapes
it will have a list of shapes: lines, rectangles, ellipses, triangles
it will have current shape
for every shape it will have a button
when a button is pressed, the current shape is changed

*/
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics.hpp"
class ShapeSelector {
private:
	// vector of buttons
	// buttons will have a name
	std::vector<tgui::Button::Ptr> _shapeButtons;
	tgui::Gui* _gui;
public:
	void draw(sf::RenderWindow& window);
	// constructor
	ShapeSelector(tgui::Gui& gui, int height);
};