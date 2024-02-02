#include "Window.h"

Window::Window() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->width = desktop.width * 0.8;
    this->height = desktop.height * 0.8;
    _gui = new tgui::Gui(_window);

    _window.create(sf::VideoMode(this->width, this->height), "Drawing Application");
    _gui->setTarget(_window);

    // Calculate canvas size and initialize it
    int canvasWidth = static_cast<int>(this->width);
    int canvasHeight = static_cast<int>(this->height * (1-barHeight));
    _canvas = new Canvas(canvasWidth, canvasHeight);

    float canvasX = (this->width - _canvas->getWidth()) / 2.0f; // Horizontally center
    float canvasY = this->height - _canvas->getHeight();        // At the bottom

    _canvas->setPosition(canvasX, canvasY);

    // init uibar
    _uiBar = new UIBar(this->width, this->height * barHeight, *_gui);
}

Window::~Window() {
	delete _canvas;
	delete _gui;
	delete _uiBar;
}
void Window::run() {
    sf::Clock clock;
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();


			sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
			if (mousePos.x >= _canvas->getPosition().x && mousePos.x <= _canvas->getPosition().x + _canvas->getWidth() &&
				mousePos.y >= _canvas->getPosition().y && mousePos.y <= _canvas->getPosition().y + _canvas->getHeight()) {
				_canvas->handleEvent(event, _window);
			}
            else if (mousePos.x >= _uiBar->getPosition().x && mousePos.x <= _uiBar->getPosition().x + _uiBar->getWidth() &&
                mousePos.y >= _uiBar->getPosition().y && mousePos.y <= _uiBar->getPosition().y + _uiBar->getHeight()) {
                _uiBar->handleEvent(event);
            }

 
            _gui->handleEvent(event); 
        }

        if (clock.getElapsedTime().asSeconds() >= 1.f / fps) {
            clock.restart();
            _window.clear();
            _uiBar->draw(_window);
            _canvas->draw(_window);
            _gui->draw(); // Draw GUI elements
            _window.display();
        }
    }
}

sf::RenderWindow& Window::getWindow() {
    return _window;
}