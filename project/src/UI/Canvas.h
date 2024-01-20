#pragma once
#include <SFML/Graphics.hpp>

/* Canvas will have a list of objects inside it, that will be rendered and shown*/
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

