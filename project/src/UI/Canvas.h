//
// Created by Rostyslav on 03.12.2023.
//

#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>

class Canvas {
public:
    Canvas(int width, int height);
    ~Canvas(); // Destructor to handle cleanup

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);

    int getWidth() const;
    int getHeight() const;

private:
    sf::RenderTexture* renderTexture;
    sf::Sprite* canvasSprite;
    int canvasWidth;
    int canvasHeight;
};

#endif // CANVAS_H



