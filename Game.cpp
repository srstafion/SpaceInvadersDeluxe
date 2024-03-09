#include "Game.h"

Game::Game() : 
    window(sf::VideoMode(750, 800), "Space Invaders DLX"),
    player(),
    /*orb(),*/
    enemyFactory(),
    frameCounter(0),
    score(0),
    menu(375, 250, 60, 110, buttons)
{
    srand(time(NULL));

    gameBG1Texture.loadFromFile("./Textures/background1.png");
    gameBG2Texture.loadFromFile("./Textures/background2.png");

    gameBG1.setSize(Vector2f(width, height));
    gameBG1.setPosition(0,0);
    gameBG1.setTexture(&gameBG1Texture);

    gameBG2.setSize(Vector2f(width, height));
    gameBG2.setPosition(0, -height);
    gameBG2.setTexture(&gameBG2Texture);

    for (int i = 0; i < 5; i++) {
        stars.push_back(Star());
    }

    background.setSize(Vector2f(width, height));
    if (!backgroundTexture.loadFromFile("./Space.jpg")) {
        cout << "Background Error";
    }
    background.setTexture(&backgroundTexture);

    if (!titleFont.loadFromFile("./Fonts/Crang.ttf")) {
        cout << "Error B";
    }
    titleText.setFont(titleFont);
    titleText.rotate(-10);
    initText(titleText, 60, 135, "Space Invaders", 60, 4, Color(57, 4, 59), Color(255, 215, 152));

    if (!subtitleFont.loadFromFile("./Fonts/VeniceClassic.ttf")) {
        cout << "Error B";
    }
    subtitleText.setFont(subtitleFont);
    initText(subtitleText, 535, 135, "(Deluxe)", 50, 3, Color(57, 4, 59), Color(255, 215, 152));


    menu.setColorTextMenu(Color::Black);
    menu.AlignMenu();
}

void Game::run()
{
    while (window.isOpen()) {
        handleEvents();
        handleInput();
        update();
        render();
        sleep(milliseconds(25));
    }
}

void Game::handleEvents()
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        //menu.GamePlayMenu(window, background, titleText, subtitleText, event);
    }
}

void Game::handleInput()
{
    if (Keyboard::isKeyPressed(Keyboard::W)) player.movePlayer(1);
    if (Keyboard::isKeyPressed(Keyboard::A)) player.movePlayer(2);
    if (Keyboard::isKeyPressed(Keyboard::S)) player.movePlayer(3);
    if (Keyboard::isKeyPressed(Keyboard::D)) player.movePlayer(4);
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        player.shoot();
        player.toggleShot(0);
    }
    else player.toggleShot(1);
}

void Game::update()
{
    //Move Bullets and Delete if they Reach the Top
    player.updateBullets();
    //Spawn a Row of Enemies every 3 Seconds
    if (enemyCooldown.getElapsedTime().asMilliseconds() >= 3000
        || enemyFactory.getEnemies().empty()) {
        enemyFactory.addRow();
        enemyCooldown.restart();
    }
    //End the Game if a Player Collides with anything
    if (collisionCheck()) {
        window.close();
    }
    //Delete Enemies if they reach the bottom and end the Game
    enemyFactory.updateEnemy();
    //Move Enemies and make them shoot, move Bullets
    for (int i = 0; i < enemyFactory.getEnemies().size(); i++) {
        enemyFactory.getEnemies()[i].update();
        //Delete Enemy if it collides with a player bullet
        for (int j = 0; j < player.getBullets().size(); j++) {
            if (player.getBullets()[j].getGlobalBounds().
                intersects(enemyFactory.getEnemies()[i].getGlobalBounds())) {
                enemyFactory.handleBulletHit(i);
                player.deleteBullet(j);
                break;
            }
        }
    }
    gameBG1.move(0, 5);
    if (gameBG1.getPosition().y >= height) gameBG1.setPosition(0, -height);
    gameBG2.move(0, 5);
    if (gameBG2.getPosition().y >= height) gameBG2.setPosition(0, -height);

    for (auto& i : stars) {
        i.commenceMovement();
    }
    /*orb.update();
    if (orb.checkCollision(player)) {
        player.additionalBulletsTimer = 100;
        updateScoreText();
    }
    if (random(1, 10) < 5 && !orb.active) {
        orb.active = true;
    }

    if (++frameCounter == 100) {
        spawnAdditionalEnemies();
        frameCounter = 0;
    }*/
}

void Game::render()
{
    window.clear();
    window.draw(gameBG1);
    window.draw(gameBG2);
    for (auto& i : stars) {
        i.draw(window);
    }
    player.show(window);
    for (auto& enemy : enemyFactory.getEnemies()) {
        enemy.show(window);
        for (auto& bullet : enemy.getBullets()) {
            bullet.showBullet(window);
        }
    }
    //window.draw(orb.shape);
    for (auto& bullet : player.getBullets()) {
        bullet.showBullet(window);
    }
    //window.draw(scoreText);
    window.display();
}

void Game::updateScoreText()
{
    scoreText.setString("Score: " + std::to_string(score));
}

bool Game::collisionCheck()
{
    for (auto& enemy : enemyFactory.getEnemies()) {
        for (auto& bullet : enemy.getBullets()) {
            if (bullet.getGlobalBounds().intersects(player.getMaskOneBounds()) ||
                bullet.getGlobalBounds().intersects(player.getMaskTwoBounds())) {
                return true;
                break;
            }
        }
    }

    for (auto& enemy : enemyFactory.getEnemies()) {
        if (player.getMaskOneBounds().intersects(enemy.getGlobalBounds()) || 
            player.getMaskTwoBounds().intersects(enemy.getGlobalBounds())) {
            return true;
            break;
        }
    }
    return false;
}

void Game::initText(Text& text, float posX, float posY, 
    string str, int sizeFont, int thickness, 
    Color menuTextColor, Color outlineColor)
{
    text.setCharacterSize(sizeFont);
    text.setPosition(posX, posY);
    text.setString(str);
    text.setFillColor(menuTextColor);
    text.setOutlineThickness(thickness);
    text.setOutlineColor(outlineColor);
}
