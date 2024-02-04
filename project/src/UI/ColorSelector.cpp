#include "ColorSelector.h"

void ColorSelector::SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture){
	button->setPosition(height * (1 - COLOR_BUTTON_SIZE) / 2 + (COLOR_BUTTON_SIZE + COLOR_BUTTON_SPACING) * height * index + startPosition, height * (1 - SHAPE_BUTTON_SIZE) / 2);
	button->setSize(height * COLOR_BUTTON_SIZE, height * COLOR_BUTTON_SIZE);
	button->getRenderer()->setTexture(texture);
	button->getRenderer()->setBorderColorFocused(sf::Color::Red);
	button->getRenderer()->setBorders({ 2, 2, 2, 2 });
}

ColorSelector::ColorSelector(tgui::Gui& gui, int height, int position){
	this->startPosition = position;
	this->height = height;

	_redColorTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "redColorButton.png");
	_redColorButton = tgui::Button::create();
	SetButtonParameters(0, _redColorButton, _redColorTexture);

	_redColorButton->onPress([] {
		Controller::setColor(sf::Color::Red);
		});
	gui.add(_redColorButton);

	_greenColorTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "greenColorButton.png");
	_greenColorButton = tgui::Button::create();
	SetButtonParameters(1, _greenColorButton, _greenColorTexture);

	_greenColorButton->onPress([] {
		Controller::setColor(sf::Color::Green);
		});
	gui.add(_greenColorButton);

	_blueColorTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "blueColorButton.png");
	_blueColorButton = tgui::Button::create();
	SetButtonParameters(2, _blueColorButton, _blueColorTexture);

	_blueColorButton->onPress([] {
		Controller::setColor(sf::Color::Blue);
		});
	gui.add(_blueColorButton);

	_blackColorTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "blackColorButton.png");
	_blackColorButton = tgui::Button::create();
	SetButtonParameters(3, _blackColorButton, _blackColorTexture);

	_blackColorButton->onPress([] {
		Controller::setColor(sf::Color::Black);
		});
	gui.add(_blackColorButton);

	_yellowColorTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "yellowColorButton.png");
	_yellowColorButton = tgui::Button::create();
	SetButtonParameters(4, _yellowColorButton, _yellowColorTexture);

	_yellowColorButton->onPress([] {
		Controller::setColor(sf::Color::Yellow);
		});
	gui.add(_yellowColorButton);

	_cyanColorTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "cyanColorButton.png");
	_cyanColorButton = tgui::Button::create();
	SetButtonParameters(5, _cyanColorButton, _cyanColorTexture);

	_cyanColorButton->onPress([] {
		Controller::setColor(sf::Color::Cyan);
		});
	gui.add(_cyanColorButton);
}

float ColorSelector::GetWidth()
{
	return height * (1 - COLOR_BUTTON_SIZE) / 2 + (COLOR_BUTTON_SIZE + COLOR_BUTTON_SPACING) * height * 6;
}

void ColorSelector::draw(){
	if (Controller::getColor() == sf::Color::Red)
		_redColorButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_redColorButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getColor() == sf::Color::Green)
		_greenColorButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_greenColorButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getColor() == sf::Color::Blue)
		_blueColorButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_blueColorButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getColor() == sf::Color::Black)
		_blackColorButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_blackColorButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getColor() == sf::Color::Yellow)
		_yellowColorButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_yellowColorButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getColor() == sf::Color::Cyan)
		_cyanColorButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_cyanColorButton->getRenderer()->setBorderColor(sf::Color::Green);

}
