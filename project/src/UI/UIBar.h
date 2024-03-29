#pragma once
/* Class for UIBar*/
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ShapeSelector.h"
#include "ColorSelector.h"
#include "LineSelector.h"
#include "ToolSelector.h"
#include "FileTool.h"
class UIBar {

	public:
	UIBar(int width, int height, tgui::Gui& gui);
	~UIBar(); 

	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event& event);
	int getWidth();
	int getHeight();
	sf::Vector2f getPosition();
private:
	sf::RenderTexture* renderTexture;
	sf::Sprite* sprite;
	tgui::Gui* _gui;
	ShapeSelector* _shapeSelector;
	ColorSelector* _colorSelector;
	LineSelector* _lineSelector;
	ToolSelector* _toolSelector;
	FileTool* _fileTool;
};