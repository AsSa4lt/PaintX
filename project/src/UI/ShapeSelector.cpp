#include "ShapeSelector.h"

void ShapeSelector::draw(){
    // if selected shape is rectangle, add border to rectangle button
	if(Controller::getShape() == Shapes::RECTANGLE)
		_rectangleButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_rectangleButton->getRenderer()->setBorderColor(sf::Color::Green);
	
	if (Controller::getShape() == Shapes::ELLIPSE)
		_ellipseButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_ellipseButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getShape() == Shapes::TRIANGLE)
		_triangleButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_triangleButton->getRenderer()->setBorderColor(sf::Color::Green);


	if (Controller::getShape() == Shapes::LINE)
		_lineButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_lineButton->getRenderer()->setBorderColor(sf::Color::Green);
}



void ShapeSelector::SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture)
{
	button->setPosition(height * (1 - SHAPE_BUTTON_SIZE) / 2 + (SHAPE_BUTTON_SIZE + SHAPE_BUTTON_SPACING) * height * index, height * (1 - SHAPE_BUTTON_SIZE) / 2);
	button->setSize(height * SHAPE_BUTTON_SIZE, height * SHAPE_BUTTON_SIZE);
	button->getRenderer()->setTexture(texture);
	button->getRenderer()->setBorderColorFocused(sf::Color::Red);
	button->getRenderer()->setBorders({ 2, 2, 2, 2 });
}

ShapeSelector::ShapeSelector(tgui::Gui& gui, int height){
	this->height = height;
	// it will be a grey rendertexture will buttons on it
	// buttons will have images of the shapes
	// when clicked, the shape will be selected
	// the shape will be drawn on the canvas
	// test button with path to image
	_rectangleTexture = tgui::Texture((std::string)PATH_TO_IMAGES+"rectangle.png");
	_rectangleButton = tgui::Button::create();
	SetButtonParameters(0, _rectangleButton, _rectangleTexture);

	_rectangleButton->onPress([] {
		Controller::setShape(Shapes::RECTANGLE);
	});
	gui.add(_rectangleButton);


	_ellipseTexture = tgui::Texture((std::string)PATH_TO_IMAGES+"ellipse.png");
	_ellipseButton = tgui::Button::create();
	SetButtonParameters(1, _ellipseButton, _ellipseTexture);

	_ellipseButton->onPress([] {
		Controller::setShape(Shapes::ELLIPSE);
	});

	gui.add(_ellipseButton);

	_triangleTexture = tgui::Texture((std::string)PATH_TO_IMAGES+"triangle.png");
	_triangleButton = tgui::Button::create();
	SetButtonParameters(2, _triangleButton, _triangleTexture);

	_triangleButton->onPress([] {
		Controller::setShape(Shapes::TRIANGLE);
	});

	gui.add(_triangleButton);

	_lineTexture = tgui::Texture((std::string)PATH_TO_IMAGES+"line.png");
	_lineButton = tgui::Button::create();
	SetButtonParameters(3, _lineButton, _lineTexture);

	_lineButton->onPress([] {
		Controller::setShape(Shapes::LINE);
		});

	gui.add(_lineButton);
}

float ShapeSelector::GetWidth(){
	return height * (1 - SHAPE_BUTTON_SIZE) / 2 + (SHAPE_BUTTON_SIZE + SHAPE_BUTTON_SPACING) * height * 4;
}
