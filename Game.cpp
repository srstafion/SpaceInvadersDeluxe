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
        /*menu.GamePlayMenu(window, background, titleText, subtitleText, event);*/
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
    player.updateBullets();
    if (enemyCooldown.getElapsedTime().asMilliseconds() >= 3000
        || enemyFactory.getEnemies().empty()) {
        enemyFactory.addRow();
        enemyCooldown.restart();
    }
    enemyFactory.moveEn();
    if (collisionCheck(player, enemyFactory)) {
        window.close();
    }
    for (int i = 0; i < enemyFactory.getEnemies().size(); i++){
        for (int j = 0; j < player.getBullets().size(); j++) {
            if (player.getBullets()[j].getGlobalBounds().
                intersects(enemyFactory.getEnemies()[i].getGlobalBounds())) {
                enemyFactory.deleteEnemy(i);
                player.deleteBullet(j);
                break;
            }
        }
    }
    /*player.update();

    if (gameUpdate(player, enemyManager)) {
        window.close();
    }

    orb.update();
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

bool Game::collisionCheck(Player& player, EnemyFactory& ef)
{
    for (auto& enemy : ef.getEnemies()) {
        for (auto& bullet : enemy.getBullets()) {
            if (bullet.getGlobalBounds().intersects(player.getGlobalBounds())) {
                return true;
                break;
            }
        }
    }

    for (auto& enemy : ef.getEnemies()) {
        for (auto& bullet : player.getBullets()) {
            if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                //handleHit
                //removeBullet
                //changeScore
                break;
            }
        }
    }

    for (auto& enemy : ef.getEnemies()) {
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
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
