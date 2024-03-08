#include "Header.h"
#include "GameMenu.h"

void GameMenu::setInitText(sf::Text& text, std::string& str, float xpos, float ypos, sf::Color color, int fontSize) {
	text.setFont(font);
	text.setFillColor(color);
	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
}

void GameMenu::AlignMenu() {
	float nullx = 0;

	for (int i = 0; i < mainMenu.size(); i++) {
		nullx = mainMenu[i].getLocalBounds().width / 2;
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}

GameMenu::GameMenu(float menux, float menuy, int sizeFont, int step, std::vector<std::string>& name)
	:menuX(menux), 
	menuY(menuy), 
	menuStep(step), 
	sizeFont(sizeFont), 
	mainMenu(name.size())
{
	if (!font.loadFromFile("./Fonts/CooperBits.ttf")) {
		// Menu Font Error
	}

	for (int i = 0, posY = menuY; i < mainMenu.size(); i++, posY += menuStep) {
		setInitText(mainMenu[i], name[i], menuX, posY, menuColor, sizeFont);
	}
}

void GameMenu::draw(sf::RenderWindow& window) {
	for (auto i : mainMenu) {
		window.draw(i);
	}
}

void GameMenu::setColorTextMenu(sf::Color color) {
	menuColor = color;
	for (auto i : mainMenu) {
		i.setFillColor(menuColor);
	}
}

void GameMenu::GamePlayMenu(sf::RenderWindow& window, sf::RectangleShape& background, sf::Text& titul, sf::Text& subtitle, sf::Event& event) {
	bool resultMenu = false;

	while (!resultMenu && window.isOpen()) {
		while (window.pollEvent(event)) {
			handleEvent(window, event, background, resultMenu);
		}
		window.clear();
		window.draw(background);
		window.draw(titul);
		window.draw(subtitle);
		draw(window);
		window.display();
	}
}

void GameMenu::handleEvent(sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background, bool& resultMenu) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	for (int i = 0; i < mainMenu.size(); i++) {
		if (mainMenu[i].getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
			mainMenu[i].setFillColor(menuColor);
		}
		else {
			mainMenu[i].setFillColor(sf::Color::White);
		}
	}

	if (event.type == sf::Event::Closed) {
		std::exit(0);
		window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		std::exit(0);
		window.close();
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		handleMouseClick(window, event, background, resultMenu, mousePosition);
	}
}

void GameMenu::handleMouseClick(sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background,
	bool& resultMenu, const sf::Vector2i& mousePosition) {
	for (int i = 0; i < mainMenu.size(); i++) {
		if (mainMenu[i].getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
			switch (i) {
			case 0:
				resultMenu = true;
				break;
			case 1:
				break;
			case 2:
				std::exit(0);
				window.close();
				break;
			}
		}
	}
}