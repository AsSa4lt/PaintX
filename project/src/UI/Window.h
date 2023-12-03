//
// Created by Rostyslav on 28.11.2023.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <TGUI/Backends/SFML.hpp>


class Window {
public:
    Window();
    void Update();
    void CreateWindow();
    int getWidth();
    void setWidth(int _width);
    int getHeight();
    void setHeight(int _height);


    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
    tgui::Gui gui;
    int height;
    int width;
    static const int fps = 60;
};



#endif //WINDOW_H
