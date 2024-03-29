
#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Canvas.h"
#include "UIBar.h"
#include "Utils/Config.h"

class Window {
public:
    Window();
    ~Window();
    void run();
    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow _window;
    tgui::Gui* _gui;
    Canvas* _canvas;
    UIBar* _uiBar;
    double barHeight = 0.08;
    int width = 800;
    int height = 600;
    static constexpr int fps = 60;
};

