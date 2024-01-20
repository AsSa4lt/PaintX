/* Class for UIBar*/
#include <SFML/Graphics.hpp>
class UIBar {

	public:
	UIBar(int width, int height);
	~UIBar(); // Destructor to handle cleanup

	void draw(sf::RenderWindow& window);
private:
	sf::RenderTexture* renderTexture;
	sf::Sprite* sprite;
};