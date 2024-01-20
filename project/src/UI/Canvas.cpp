#include "Canvas.h"
Canvas::Canvas(int width, int height) : canvasWidth(width), canvasHeight(height) {
    renderTexture = new sf::RenderTexture();
    if (renderTexture->create(width, height)) {
        canvasSprite = new sf::Sprite(renderTexture->getTexture());
    }

    renderTexture->clear(sf::Color::Blue);
}

Canvas::~Canvas() {
    delete canvasSprite;
    delete renderTexture;
}

void Canvas::handleEvent(const sf::Event& event) {
    // Handle events here...
}

void Canvas::draw(sf::RenderWindow& window) {
    renderTexture->display();
    window.draw(*canvasSprite);
}

void Canvas::setPosition(float x, float y) {
    canvasSprite->setPosition(x, y);
}

int Canvas::getWidth() const {
    return canvasWidth;
}

int Canvas::getHeight() const {
    return canvasHeight;
}
