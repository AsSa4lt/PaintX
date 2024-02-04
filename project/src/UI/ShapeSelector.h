
#pragma once
/* Selector of shapes
it will have a list of shapes: lines, rectangles, ellipses, triangles
it will have current shape
for every shape it will have a button
when a button is pressed, the current shape is changed

*/
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"
#include "Utils/Config.h"
class ShapeSelector {
private:
	tgui::Button::Ptr _rectangleButton;
	tgui::Texture _rectangleTexture;
	tgui::Button::Ptr _ellipseButton;
	tgui::Texture _ellipseTexture;
	tgui::Button::Ptr _lineButton;
	tgui::Texture _lineTexture;
	tgui::Button::Ptr _triangleButton;
	tgui::Texture _triangleTexture;
	tgui::CheckBox::Ptr _fillCheckBox;
	int height;
	void SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture);
public:
	void draw();
	// constructor
	ShapeSelector(tgui::Gui& gui, int height);
	float GetWidth();
};