//
// Created by Rostyslav on 28.11.2023.
//

#include "Window.h"

Window::Window() {}

int Window::getWidth() {
    return width;
}

void Window::setWidth(int _width) {
    width = _width;
}

int Window::getHeight() {
    return height;
}

void Window::setHeight(int _height) {
    height = _height;
}

void Window::Update() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.0f / fps);



    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                gui.handleEvent(event);
            }
        }

        // Clear screen with white color
        window.clear(sf::Color::Black);
        // Draw your GUI
        gui.draw();

        // Display everything
        window.display();

        // GraphDisplay
    }
}


void Window::CreateWindow() {
    window.create(sf::VideoMode(width, height),"PaintX");
    gui.setTarget(window);
    // will be added UI elemnts here, i dont really want to implement my own vision of buttons with SFML, so it will be TGUI

}

sf::RenderWindow& Window::getWindow() {
    return window;
}
