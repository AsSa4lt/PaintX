#include "Canvas.h"
Canvas::Canvas(int width, int height) : canvasWidth(width), canvasHeight(height) {
    renderTexture = new sf::RenderTexture();
    if (renderTexture->create(width, height)) {
        canvasSprite = new sf::Sprite(renderTexture->getTexture());
    }

    renderTexture->clear(sf::Color::White);
	// init objects vector
}

Canvas::~Canvas() {
    delete canvasSprite;
    delete renderTexture;
}

void Canvas::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    // logic is simple, as in Paint, if we click and hold, draw(will we implemented)
	// if we release, stop drawing
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			// remeber startPosition
			isDrawing = true;
			// get position by percentage of screen, convert start position to percentage
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			// convert to percentage
			sf::Vector2f start = sf::Vector2f(mouse.x / window.getSize().x, mouse.y / window.getSize().y);

			Object* object = ObjectsFactory::createObject(start, start);
			Controller::setCurrentObject(object);

			if (Controller::getTool() == Tool::ERASER) {
				for(auto& object : Controller::getObjects()) {
					if (object != nullptr && object->isInside(mouse, window)) {
						Controller::RemoveObject(object);
					}
				}
			}

			if (Controller::getTool() == Tool::RESIZE || Controller::getTool() == Tool::MOVE) {
				for(auto& object : Controller::getObjects()) {
					if (object != nullptr && object->isInside(mouse, window)) {
						Controller::setMovingObject(object);
						break;
					}
				}
				startPosition = start;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			// release the last object
			isDrawing = false;
			Controller::AddObject(Controller::getCurrentObject());
			
			Controller::setCurrentObject(nullptr);
			Controller::setMovingObject(nullptr);
		}
	}
	else if (event.type == sf::Event::MouseMoved) {
		// if we are holding the mouse, update current object
		// update the end position of the object
		if (isDrawing) {
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			// convert to percentage
			mouse.x /= window.getSize().x;
			mouse.y /= window.getSize().y;
			if(Controller::getCurrentObject() != nullptr && Controller::getTool() != Tool::RESIZE && Controller::getTool() != Tool::MOVE)
				Controller::getCurrentObject()->setEnd(mouse);

			if (Controller::getMovingObject() != nullptr && (Controller::getTool() == Tool::RESIZE || Controller::getTool() == Tool::MOVE)) {
				//move end and start position
				sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				// convert to percentage
				sf::Vector2f end = sf::Vector2f(mouse.x / window.getSize().x, mouse.y / window.getSize().y);
				if(Controller::getTool() == Tool::RESIZE)
					Controller::getMovingObject()->resize(end - startPosition);
				else
					Controller::getMovingObject()->move(end - startPosition);
				startPosition = end;

			}
		}
	}
}

void Canvas::draw(sf::RenderWindow& window) {
	// draw the canvas
	window.draw(*canvasSprite);
    // get all objects and draw them from Controller
	for (auto& object : Controller::getObjects()) {
		if(object != nullptr)
			object->draw(window);
	}

	// draw current object if not nullptr
	if (Controller::getCurrentObject() != nullptr)
		Controller::getCurrentObject()->draw(window);

	// clear the rendeer 
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
