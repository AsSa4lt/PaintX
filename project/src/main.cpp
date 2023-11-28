#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PaintX");
    tgui::Gui gui{window};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Draw with SFML here

        gui.draw(); // Draw with TGUI here
        window.display();
    }

    return 0;
}
