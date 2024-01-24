/*static class for storing intsrument and colors*/
#include <SFML/Graphics.hpp>
#include "Window.h"

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

class Controller {
	static Instrument instrument;
	static sf::Color color;
	static Window* window;
	static void setWindow(Window* window);
	static Window* getWindow();
	static void setInstrument(Instrument instrument);
	static Instrument getInstrument();
};