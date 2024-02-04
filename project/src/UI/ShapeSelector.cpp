#include "ShapeSelector.h"

void ShapeSelector::draw(sf::RenderWindow& window){
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

ShapeSelector::ShapeSelector(tgui::Gui& gui, int height){
	// it will be a grey rendertexture will buttons on it
	// buttons will have images of the shapes
	// when clicked, the shape will be selected
	// the shape will be drawn on the canvas
	// test button with path to image
	_rectangleTexture = tgui::Texture("../../../../src/images/rectangle.png");
	_rectangleButton = tgui::Button::create();
	_rectangleButton->setPosition(height * (1 - SHAPE_BUTTON_SIZE)/2, height * (1 - SHAPE_BUTTON_SIZE) / 2);
	_rectangleButton->setSize(height * SHAPE_BUTTON_SIZE, height * SHAPE_BUTTON_SIZE);
	_rectangleButton->getRenderer()->setTexture(_rectangleTexture);
	_rectangleButton->getRenderer()->setBorderColorFocused(sf::Color::Red);
	_rectangleButton->getRenderer()->setBorders({ 2, 2, 2, 2 });

	_rectangleButton->onPress([] {
		Controller::setShape(Shapes::RECTANGLE);
	});
	gui.add(_rectangleButton);


	_ellipseTexture = tgui::Texture("../../../../src/images/ellipse.png");
	_ellipseButton = tgui::Button::create();
	_ellipseButton->setPosition(height * (1 - SHAPE_BUTTON_SIZE) / 2 + (SHAPE_BUTTON_SIZE + SHAPE_BUTTON_SPACING) * height, height * (1 - SHAPE_BUTTON_SIZE) / 2);
	_ellipseButton->setSize(height * SHAPE_BUTTON_SIZE, height * SHAPE_BUTTON_SIZE);
	_ellipseButton->getRenderer()->setTexture(_ellipseTexture);
	_ellipseButton->getRenderer()->setBorderColorFocused(sf::Color::Red);
	_ellipseButton->getRenderer()->setBorders({ 2, 2, 2, 2 });

	_ellipseButton->onPress([] {
		Controller::setShape(Shapes::ELLIPSE);
	});

	gui.add(_ellipseButton);

	_triangleTexture = tgui::Texture("../../../../src/images/triangle.png");
	_triangleButton = tgui::Button::create();
	_triangleButton->setPosition(height * (1 - SHAPE_BUTTON_SIZE) / 2 + (SHAPE_BUTTON_SIZE + SHAPE_BUTTON_SPACING) * height * 2, height * (1 - SHAPE_BUTTON_SIZE) / 2);
	_triangleButton->setSize(height * SHAPE_BUTTON_SIZE, height * SHAPE_BUTTON_SIZE);
	_triangleButton->getRenderer()->setTexture(_triangleTexture);
	_triangleButton->getRenderer()->setBorderColorFocused(sf::Color::Red);
	_triangleButton->getRenderer()->setBorders({ 2, 2, 2, 2 });

	_triangleButton->onPress([] {
		Controller::setShape(Shapes::TRIANGLE);
	});

	gui.add(_triangleButton);

	_lineTexture = tgui::Texture("../../../../src/images/line.png");
	_lineButton = tgui::Button::create();
	_lineButton->setPosition(height * (1 - SHAPE_BUTTON_SIZE) / 2 + (SHAPE_BUTTON_SIZE + SHAPE_BUTTON_SPACING) * height * 3, height * (1 - SHAPE_BUTTON_SIZE) / 2);
	_lineButton->setSize(height * SHAPE_BUTTON_SIZE, height * SHAPE_BUTTON_SIZE);
	_lineButton->getRenderer()->setTexture(_lineTexture);
	_lineButton->getRenderer()->setBorderColorFocused(sf::Color::Red);
	_lineButton->getRenderer()->setBorders({ 2, 2, 2, 2 });

	_lineButton->onPress([] {
		Controller::setShape(Shapes::LINE);
		});

	gui.add(_lineButton);
}
