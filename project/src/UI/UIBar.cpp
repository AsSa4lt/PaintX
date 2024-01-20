#include "UIBar.h"

UIBar::UIBar(int width, int height){
    renderTexture = new sf::RenderTexture();
    if (renderTexture->create(width, height)) {
        sprite = new sf::Sprite(renderTexture->getTexture());
    }

    renderTexture->clear(sf::Color::Green);
    // set position
    sprite->setPosition(0, 0);    
}

UIBar::~UIBar(){
    delete renderTexture;
    delete sprite;
}

void UIBar::draw(sf::RenderWindow& window){
	renderTexture->display();
	window.draw(*sprite);
}
