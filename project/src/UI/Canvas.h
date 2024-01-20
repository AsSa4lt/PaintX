#pragma once
#include <SFML/Graphics.hpp>
#include "Objects/Object.h"

/* Canvas will have a list of objects inside it, that will be rendered and shown*/
enum class Instrument {
    NONE,
	PENCIL,
	ERASER,
	LINE,
	RECTANGLE,
	ELLIPS,
	TRIANGLE,
	SELECT
};


class Canvas {
public:
    Canvas(int width, int height);
    ~Canvas(); // Destructor to handle cleanup

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    int getWidth() const;
    int getHeight() const;
    bool isDrawing = false;
    sf::Vector2f startPosition = sf::Vector2f(0, 0);

    // vector of objects
    std::vector<std::shared_ptr<Object>> objects;

private:
    sf::RenderTexture* renderTexture;
    sf::Sprite* canvasSprite;
    int canvasWidth;
    int canvasHeight;
    Instrument currentInstrument = Instrument::PENCIL;
};

