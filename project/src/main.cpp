#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "UI/Window.h"


int main() {
    Window window;
    window.run();
    delete &window;
    return 0;
}

