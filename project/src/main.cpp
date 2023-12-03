#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "UI/Window.h"


int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    Window mainWindow;
    mainWindow.setWidth(desktop.width);
    mainWindow.setHeight(desktop.height);
    mainWindow.CreateWindow();

    mainWindow.Update();

    return 0;
}
