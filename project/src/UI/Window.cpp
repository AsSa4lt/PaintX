#include "Window.h"

Window::Window() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->width = desktop.width * 0.8;
    this->height = desktop.height * 0.8;
    _gui = new tgui::Gui(_window);

    _window.create(sf::VideoMode(this->width, this->height), "PaintX");
    sf::Image icon;
    if (icon.loadFromFile((std::string)PATH_TO_IMAGES + "logo.png")) { // Replace "icon.png" with the path to your icon file
        _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    _gui->setTarget(_window);

    // Calculate canvas size and initialize it
    int canvasWidth = static_cast<int>(sf::VideoMode::getDesktopMode().width);
    int canvasHeight = static_cast<int>(sf::VideoMode::getDesktopMode().height * (1-barHeight));
    _canvas = new Canvas(canvasWidth, canvasHeight);

    float canvasX = (this->width - _canvas->getWidth()) / 2.0f; // Horizontally center
    float canvasY = this->height*barHeight;        // At the bottom

    _canvas->setPosition(canvasX, canvasY);

    // init uibar
    _uiBar = new UIBar(sf::VideoMode::getDesktopMode().width, this->height * barHeight, *_gui);
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

            if (event.type == sf::Event::Resized) {
                // Enforce minimum size constraints
                unsigned int newWidth = std::max(event.size.width, static_cast<unsigned int>(_window.getSize().x * MINIMUM_WIDTH));
                unsigned int newHeight = std::max(event.size.height, static_cast<unsigned int>(_window.getSize().y * MINIMUM_HEIGHT));

                // If the new size is less than half the screen size, adjust the window size
                if (newWidth < sf::VideoMode::getDesktopMode().width / 2 || newHeight < sf::VideoMode::getDesktopMode().height / 2) {
                    newWidth = std::max(newWidth, sf::VideoMode::getDesktopMode().width / 2);
                    newHeight = std::max(newHeight, sf::VideoMode::getDesktopMode().height / 2);
                    _window.setSize(sf::Vector2u(newWidth, newHeight));
                }

                // Update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, newWidth, newHeight);
                _window.setView(sf::View(visibleArea));
            }
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
            _window.clear(sf::Color::White);
            _canvas->draw(_window);
            _uiBar->draw(_window);
            _gui->draw(); // Draw GUI elements
            _window.display();
        }
    }
}

sf::RenderWindow& Window::getWindow() {
    return _window;
}
