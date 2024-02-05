#pragma once
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics.hpp"
#include "Controllers/Controller.h"
#include "Utils/Config.h"

class ToolSelector {
private:
	tgui::Button::Ptr _eraserButton;
	tgui::Texture _eraserTexture;

	tgui::Button::Ptr _resizeButton;
	tgui::Texture _resizeTexture;

	tgui::Button::Ptr _moveButton;
	tgui::Texture _moveTexture;
	int startPosition;
	float height;
	void SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture);
public:
	ToolSelector(tgui::Gui& gui, int height, int position);
	float GetWidth();
	void draw();
};