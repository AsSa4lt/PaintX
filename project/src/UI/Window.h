//
// Created by Rostyslav on 28.11.2023.
//
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
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

#endif // WINDOW_H

