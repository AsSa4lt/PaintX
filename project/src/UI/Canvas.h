#pragma once
#include <SFML/Graphics.hpp>
#include "Objects/Object.h"
#include "Controllers/Controller.h"
#include "Canvas.h"
#include "Controllers/ObjectsFactory.h"

class Canvas {
public:
    Canvas(int width, int height);
    ~Canvas(); // Destructor to handle cleanup

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    int getWidth() const;
    int getHeight() const;
    bool isDrawing = false;
    sf::Vector2i startPosition = sf::Vector2i(0, 0);

private:
    sf::RenderTexture* renderTexture;
    sf::Sprite* canvasSprite;
    int canvasWidth;
    int canvasHeight;
};

