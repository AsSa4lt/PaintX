#include "ToolSelector.h"

void ToolSelector::SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture){
	button->setPosition(height * (1 - TOOL_BUTTON_SIZE) / 2 + (TOOL_BUTTON_SIZE + TOOL_BUTTON_SPACING) * height * index + startPosition, height * (1 - TOOL_BUTTON_SIZE) / 2);
	button->setSize(height * TOOL_BUTTON_SIZE, height * TOOL_BUTTON_SIZE);
	button->getRenderer()->setTexture(texture);
	button->getRenderer()->setBorderColorFocused(sf::Color::Red);
	button->getRenderer()->setBorders({ 2, 2, 2, 2 });
}

ToolSelector::ToolSelector(tgui::Gui& gui, int height, int position){
	this->height = height;
	this->startPosition = position;

	_eraserTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "eraserColorButton.png");
	_eraserButton = tgui::Button::create();
	SetButtonParameters(0, _eraserButton, _eraserTexture);

	_eraserButton->onPress([] {
		Controller::setTool(Tool::ERASER);
	});
	gui.add(_eraserButton);

	_resizeTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "selectorColorButton.png");
	_resizeButton = tgui::Button::create();
	SetButtonParameters(1, _resizeButton, _resizeTexture);

	_resizeButton->onPress([] {
		Controller::setTool(Tool::RESIZE);
		});
	gui.add(_resizeButton);

	_moveTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "moveButton.png");
	_moveButton = tgui::Button::create();
	SetButtonParameters(2, _moveButton, _moveTexture);

	_moveButton->onPress([] {
		Controller::setTool(Tool::MOVE);
		});
	gui.add(_moveButton);
}

float ToolSelector::GetWidth(){
	return height * (1 - TOOL_BUTTON_SIZE) / 2 + (TOOL_BUTTON_SIZE + TOOL_BUTTON_SPACING) * height * 3;
}


void ToolSelector::draw(){
	if (Controller::getTool() == Tool::ERASER)
		_eraserButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_eraserButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getTool() == Tool::RESIZE)
		_resizeButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_resizeButton->getRenderer()->setBorderColor(sf::Color::Green);

	if (Controller::getTool() == Tool::MOVE)
		_moveButton->getRenderer()->setBorderColor(sf::Color::Red);
	else
		_moveButton->getRenderer()->setBorderColor(sf::Color::Green);
}
