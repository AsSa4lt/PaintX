#include "Canvas.h"
Canvas::Canvas(int width, int height) : canvasWidth(width), canvasHeight(height) {
    renderTexture = new sf::RenderTexture();
    if (renderTexture->create(width, height)) {
        canvasSprite = new sf::Sprite(renderTexture->getTexture());
    }

    renderTexture->clear(sf::Color::White);
	// init objects vector
    objects = std::vector<std::shared_ptr<Object>>();
}

Canvas::~Canvas() {
    delete canvasSprite;
    delete renderTexture;
}

void Canvas::handleEvent(const sf::Event& event) {
    	
}

void Canvas::draw(sf::RenderWindow& window) {
    renderTexture->display();
    //draw each object
    for(auto& obj : objects) {
		obj->draw(window);
	}
	window.draw(*canvasSprite);
}

void Canvas::setPosition(float x, float y) {
    canvasSprite->setPosition(x, y);
}

sf::Vector2f Canvas::getPosition() const{
    return canvasSprite->getPosition();
}

int Canvas::getWidth() const {
    return canvasWidth;
}

int Canvas::getHeight() const {
    return canvasHeight;
}
