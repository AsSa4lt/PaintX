#include "ShapeSelector.h"

void ShapeSelector::draw(sf::RenderWindow& window){
	
}

ShapeSelector::ShapeSelector(tgui::Gui& gui, int height){
	// it will be a grey rendertexture will buttons on it
	// buttons will have images of the shapes
	// when clicked, the shape will be selected
	// the shape will be drawn on the canvas
	// test button with path to image
	auto texture = tgui::Texture("../../../../src/images/rectangle.png");
	auto rectangle = tgui::Button::create();
	rectangle->setPosition(height * 0.1, height * 0.1);
	rectangle->setSize(height * 0.8, height * 0.8);
	rectangle->getRenderer()->setTexture(texture);
	gui.add(rectangle);

}


