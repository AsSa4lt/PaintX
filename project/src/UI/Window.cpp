#include "Window.h"

Window::Window() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->width = desktop.width;
    this->height = desktop.height;

    _window.create(sf::VideoMode(this->width, this->height), "Drawing Application");
    _gui.setTarget(_window);

    // Calculate canvas size and initialize it
    int canvasWidth = static_cast<int>(this->width/1.02);
    int canvasHeight = static_cast<int>(this->height/1.05);
    _canvas = new Canvas(canvasWidth, canvasHeight);

    float canvasX = (this->width - _canvas->getWidth()) / 2.0f; // Horizontally center
    float canvasY = this->height - _canvas->getHeight();        // At the bottom

    _canvas->setPosition(canvasX, canvasY);

    // Initialize GUI elements here if any
}


void Window::run() {
    sf::Clock clock;
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            _canvas->handleEvent(event);
            _gui.handleEvent(event); // If you have GUI events
        }

        if (clock.getElapsedTime().asSeconds() >= 1.f / fps) {
            clock.restart();
            _window.clear();
            _canvas->draw(_window);
            _gui.draw(); // Draw GUI elements
            _window.display();
        }
    }
}

sf::RenderWindow& Window::getWindow() {
    return _window;
}
