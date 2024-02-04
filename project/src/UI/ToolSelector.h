#pragma once
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"
#include "Utils/Config.h"

class ToolSelector {
private:
	tgui::Button::Ptr _eraserButton;
	tgui::Texture _eraserTexture;

	tgui::Button::Ptr _selectorButton;
	tgui::Texture _selectorTexture;
	int startPosition;
	float height;
	void SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture);
public:
	ToolSelector(tgui::Gui& gui, int height, int position);
	float GetWidth();
	void draw();
};