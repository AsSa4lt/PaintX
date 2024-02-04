#pragma once

#include "TGUI/TGUI.hpp"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"
#include "Utils/Config.h"

class ColorSelector {
private:
	tgui::Button::Ptr _redColorButton;
	tgui::Texture _redColorTexture;

	tgui::Button::Ptr _greenColorButton;
	tgui::Texture _greenColorTexture;

	tgui::Button::Ptr _blueColorButton;
	tgui::Texture _blueColorTexture;

	tgui::Button::Ptr _blackColorButton;
	tgui::Texture _blackColorTexture;

	tgui::Button::Ptr _yellowColorButton;
	tgui::Texture _yellowColorTexture;

	tgui::Button::Ptr _cyanColorButton;
	tgui::Texture _cyanColorTexture;
	int startPosition;
	float height;
	void SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture);
public:
	ColorSelector(tgui::Gui& gui, int height, int position);
	float GetWidth();
	void draw();
};