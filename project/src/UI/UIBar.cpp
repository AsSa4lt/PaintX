#include "UIBar.h"

UIBar::UIBar(int width, int height, tgui::Gui& gui){
    renderTexture = new sf::RenderTexture();
    if (renderTexture->create(width, height)) {
        sprite = new sf::Sprite(renderTexture->getTexture());
    }
    // set grey background
    renderTexture->clear(sf::Color(20, 20, 20));
    // set position
    sprite->setPosition(0, 0);  
    _gui = &gui;

    _shapeSelector = new ShapeSelector(*_gui, height);
    _colorSelector = new ColorSelector(*_gui, height, _shapeSelector->GetWidth());
    _lineSelector = new LineSelector(*_gui, height, _shapeSelector->GetWidth() + _colorSelector->GetWidth());
    _toolSelector = new ToolSelector(*_gui, height, _shapeSelector->GetWidth() + _colorSelector->GetWidth() + _lineSelector->GetWidth());
    _fileTool = new FileTool(*_gui, height, _shapeSelector->GetWidth() + _colorSelector->GetWidth() + _lineSelector->GetWidth() + _toolSelector->GetWidth());
}

UIBar::~UIBar(){
    delete renderTexture;
    delete sprite;
}

void UIBar::draw(sf::RenderWindow& window){
	renderTexture->display();
	window.draw(*sprite);
    _shapeSelector->draw();
    _colorSelector->draw();
    _lineSelector->draw();
    _toolSelector->draw();
    _fileTool->draw();
}

void UIBar::handleEvent(sf::Event& event){
}

int UIBar::getWidth(){
    return renderTexture->getSize().x;
}

int UIBar::getHeight(){
    return renderTexture->getSize().y;
}

sf::Vector2f UIBar::getPosition(){
    return sprite->getPosition();
}
