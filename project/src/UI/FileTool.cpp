#include "FileTool.h"

void FileTool::SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture) {
	button->setPosition(height * (1 - TOOL_BUTTON_SIZE) / 2 + (TOOL_BUTTON_SIZE + TOOL_BUTTON_SPACING) * height * index + startPosition, height * (1 - TOOL_BUTTON_SIZE) / 2);
	button->setSize(height * TOOL_BUTTON_SIZE, height * TOOL_BUTTON_SIZE);
	button->getRenderer()->setTexture(texture);
	button->getRenderer()->setBorderColorFocused(sf::Color::Green);
	button->getRenderer()->setBorders({ 2, 2, 2, 2 });
}

FileTool::FileTool(tgui::Gui& gui, int height, int position) {
	this->height = height;
	this->startPosition = position;

	_openButtonTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "saveButton.png");
	_openButton = tgui::Button::create();
	SetButtonParameters(0, _openButton, _openButtonTexture);

	_openButton->onPress([] {
		// open explorer to select file, create file with only ending .pnx
		// Load to Saver::Save

	});
	gui.add(_openButton);

	_saveButtonTexture = tgui::Texture((std::string)PATH_TO_IMAGES + "openButton.png");
	_saveButton = tgui::Button::create();
	SetButtonParameters(1, _saveButton, _saveButtonTexture);

	_saveButton->onPress([] {
		//open explorer to select file, select file with only ending .pnx
		// Load to Saver::Load

	});
	gui.add(_saveButton);
}


float FileTool::GetWidth() {
	return height * (1 - TOOL_BUTTON_SIZE) / 2 + (TOOL_BUTTON_SIZE + TOOL_BUTTON_SPACING) * height * 6;
}


void FileTool::draw() {
	_openButton->getRenderer()->setBorderColor(sf::Color::Green);
	_saveButton->getRenderer()->setBorderColor(sf::Color::Green);
}

