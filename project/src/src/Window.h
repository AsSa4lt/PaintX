#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Canvas.h"

class Window {
public:
    Window();
    void run();
    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow _window;
    tgui::Gui _gui;
    Canvas* _canvas;
    int width = 800;
    int height = 600;
    static constexpr int fps = 60;
};


