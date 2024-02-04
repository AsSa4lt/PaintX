#include "LineSelector.h"

void LineSelector::SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture){
	button->setPosition(height * (1 - LINE_BUTTON_SIZE) / 2 + (LINE_BUTTON_SIZE + LINE_BUTTON_SPACING) * height * index + startPosition, height * (1 - LINE_BUTTON_SIZE) / 2);
	button->setSize(height * LINE_BUTTON_SIZE, height * LINE_BUTTON_SIZE);
	button->getRenderer()->setTexture(texture);
	button->getRenderer()->setBorderColorFocused(sf::Color::Red);
	button->getRenderer()->setBorders({ 2, 2, 2, 2 });
}

LineSelector::LineSelector(tgui::Gui& gui, int height, int position){
	this->startPosition = position;
	this->height = height;

	_smallLineTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "smallColorButton.png");
	_smallLineButton = tgui::Button::create();
	SetButtonParameters(0, _smallLineButton, _smallLineTexture);

	_smallLineButton->onPress([] {
		Controller::setLineSize(LineSize::SMALL);
		});
	gui.add(_smallLineButton);

	_meidumLineTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "meidumColorButton.png");
	_mediumLineButton = tgui::Button::create();
	SetButtonParameters(1, _mediumLineButton, _meidumLineTexture);

	_mediumLineButton->onPress([] {
		Controller::setLineSize(LineSize::MEDIUM);
		});
	gui.add(_mediumLineButton);

	_largeLineTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "largeColorButton.png");
	_largeLineButton = tgui::Button::create();
	SetButtonParameters(2, _largeLineButton, _largeLineTexture);

	_largeLineButton->onPress([] {
		Controller::setLineSize(LineSize::LARGE);
		});
	gui.add(_largeLineButton);
}

void LineSelector::draw(){
	if (Controller::getLineSizeParameter() == LineSize::SMALL)
		_smallLineButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_smallLineButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getLineSizeParameter() == LineSize::MEDIUM)
		_mediumLineButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_mediumLineButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getLineSizeParameter() == LineSize::LARGE)
		_largeLineButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_largeLineButton->getRenderer()->setBorderColor(sf::Color::Green);
}

float LineSelector::GetWidth(){
	return height * (1 - LINE_BUTTON_SIZE) / 2 + (LINE_BUTTON_SIZE + LINE_BUTTON_SPACING) * height * 3;
}
