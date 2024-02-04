#pragma "once"
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include "Controllers/Controller.h"
#include "Utils/Config.h"

class LineSelector {
private:
	tgui::Button::Ptr _smallLineButton;
	tgui::Texture _smallLineTexture;

	tgui::Button::Ptr _mediumLineButton;
	tgui::Texture _meidumLineTexture;

	tgui::Button::Ptr _largeLineButton;
	tgui::Texture _largeLineTexture;
	int startPosition;
	float height;
	void SetButtonParameters(int index, tgui::Button::Ptr button, tgui::Texture& texture);
public:
	LineSelector(tgui::Gui& gui, int height, int position);
	void draw();
	float GetWidth();
};