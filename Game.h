#pragma once
#include "Header.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "GameMenu.h"
#include "Star.h"

class Game {
private:
    RenderWindow window;
    float width = 750;
    float height = 800;

    RectangleShape gameBG1;
    RectangleShape gameBG2;
    RectangleShape spinningPlanet;
    Texture gameBG1Texture;
    Texture gameBG2Texture;
    Texture spinningPlanetTexture;
    vector<Star> stars;

    Player player;
    EnemyFactory enemyFactory;
    Clock enemyCooldown;

    //Orb orb;

    int frameCounter;
    int score;

    Text scoreText;
    vector<string> buttons{ "Play", "Rules", "Exit" };
    GameMenu menu;

    RectangleShape background;
    Texture backgroundTexture;

    Font titleFont;
    Text titleText;

    Font subtitleFont;
    Text subtitleText;
public:

    Game();

    void run();

    void handleEvents();

    void handleInput();

    void update();

    void render();

    void updateScoreText();

    bool collisionCheck();

    void initText(Text& text, float posX, float posY,
        string str, int sizeFont, int thickness,
        Color menuTextColor, Color outlineColor);
};