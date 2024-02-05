#pragma once

#include "TGUI/TGUI.hpp"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"
#include "Utils/Config.h"
#include "Utils/Saver.h"

class FileTool {
private:
	tgui::Button::Ptr _openButton;
	tgui::Texture _openButtonTexture;

	tgui::Button::Ptr _saveButton;
	tgui::Texture _saveButtonTexture;
	int startPosition;
	float height;
	void SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture);
public:
	FileTool(tgui::Gui& gui, int height, int position);
	float GetWidth();
	void draw();
};