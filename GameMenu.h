#pragma once
#include "Header.h"
using namespace std;
using namespace sf;
class GameMenu {
private:
	float menuX;
	float menuY;
	int menuStep;
	int sizeFont;
	int mainMenuSelected;

	sf::Font font;

	std::vector<sf::Text> mainMenu;
	int textPosX = 250, textPosY = 500;

	sf::Color menuColor;

	void setInitText(sf::Text& text, std::string& str, float xpos, float ypos, sf::Color color, int fontSize);

	void handleEvent(sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background, bool& resultMenu);

	void handleMouseClick(sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background,
		bool& resultMenu, const sf::Vector2i& mousePosition);
public:
	GameMenu(float menux, float menuy, int sizeFont, int step, std::vector<std::string>& name);

	void draw(sf::RenderWindow& window);

	void setColorTextMenu(sf::Color color);

	void AlignMenu();

	void GamePlayMenu(sf::RenderWindow& window, sf::RectangleShape& background, sf::Text& titul, sf::Text& subtitle, sf::Event& event);
};