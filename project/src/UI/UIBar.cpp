#include "UIBar.h"

UIBar::UIBar(int width, int height, tgui::Gui& gui){
    renderTexture = new sf::RenderTexture();
    if (renderTexture->create(width, height)) {
        sprite = new sf::Sprite(renderTexture->getTexture());
    }
    // set grey background
    renderTexture->clear(sf::Color(50, 50, 50));
    // set position
    sprite->setPosition(0, 0);  
    _gui = &gui;

    _shapeSelector = new ShapeSelector(*_gui, height);
}

UIBar::~UIBar(){
    delete renderTexture;
    delete sprite;
}

void UIBar::draw(sf::RenderWindow& window){
	renderTexture->display();
	window.draw(*sprite);
    _shapeSelector->draw(window);
}
