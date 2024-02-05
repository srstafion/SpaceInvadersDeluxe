#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <random>
#define random(a, b) (a + rand() % (b + 1 - a))
sf::Color TEXTCOLOR = sf::Color::White;
sf::Font FONT;

class Bullet {
public:
    sf::RectangleShape shape;
    bool markForRemoval = false;
    bool enemyBullet = false;

    Bullet(float startX, float startY, bool isEnemyBullet = false) {
        shape.setSize(sf::Vector2f(5, 15));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(startX, startY);
        enemyBullet = isEnemyBullet;
    }

    void update() {
        if (enemyBullet) {
            shape.move(0, 7);
        }
        else {
            shape.move(0, -20);
        }
    }
};

class Player {
public:
    sf::RectangleShape shape;
    std::vector<Bullet> bullets;
    bool shot = false;
    int additionalBulletsTimer = 0;
    int score = 0;

    Player() {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(350, 750);
    }

    void moveLeft() {
        if (shape.getPosition().x > 0) shape.move(-10, 0);
    }

    void moveRight() {
        if (shape.getPosition().x < 700) shape.move(10, 0);
    }

    void moveUp() {
        if (shape.getPosition().y > 0) shape.move(0, -10);
    }

    void moveDown() {
        if (shape.getPosition().y < 750) shape.move(0, 10);
    }

    void shoot() {
        if (!shot) {
            Bullet bullet(shape.getPosition().x + 24, shape.getPosition().y);
            bullets.push_back(bullet);

            if (additionalBulletsTimer > 0) {
                Bullet leftBullet(shape.getPosition().x, shape.getPosition().y);
                Bullet rightBullet(shape.getPosition().x + 48, shape.getPosition().y);
                bullets.push_back(leftBullet);
                bullets.push_back(rightBullet);
            }
        }
    }

    void update() {
        for (auto& bullet : bullets) {
            bullet.update();
        }
        if (additionalBulletsTimer > 0) {
            additionalBulletsTimer--;
        }
    }
};

class Orb {
public:
    sf::RectangleShape shape;
    bool active = false;

    Orb() {
        shape.setSize(sf::Vector2f(10, 10));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(random(0, 750 - 20), 800);
    }

    void update() {
        if (active) {
            shape.move(0, -0.2);
            if (shape.getPosition().y > 800) {
                active = false;
                shape.setPosition(random(0, 750 - 20), 800);
            }
        }
    }

    bool checkCollision(Player& player) {
        if (active && shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
            active = false;  // Change this line
            shape.setPosition(random(0, 750 - 20), 800);
            return true;
        }
        return false;
    }
};

class Enemy {
public:
    sf::RectangleShape shape;
    sf::Clock shootCooldown;
    std::vector<Bullet> enemyBullets;
    int hitCount = 0;
    bool markForRemoval = false;

    Enemy(float x, float y) {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        shootCooldown.restart();
    }

    void update() {
        shape.move(0, 1);
        shoot();

        for (int i = 0; i < enemyBullets.size(); i++) {
            enemyBullets[i].update();
            if (enemyBullets[i].shape.getPosition().y > 800) {
                enemyBullets[i] = enemyBullets.back();
                enemyBullets.pop_back();
                i--;
            }
        }
    }

    void shoot() {
        if (random(1, 1000) < 4) {
            float bulletX = shape.getPosition().x + shape.getSize().x / 2;
            float bulletY = shape.getPosition().y + shape.getSize().y;

            Bullet bullet(bulletX, bulletY, true);
            enemyBullets.push_back(bullet);
        }
    }

    void handleBulletHit() {
        hitCount++;

        if (hitCount == 1) {
            shape.setFillColor(sf::Color::Yellow);
        }
        else if (hitCount == 2) {
            shape.setFillColor(sf::Color::Green);
        }
        else if (hitCount == 3) {
            markForRemoval = true;
        }
    }
};

class EnemyManager {
public:
    std::vector<Enemy> enemies;

    EnemyManager() {
        int pattern = rand() % 3;

        if (pattern == 0) {
            for (int i = 1; i < 7; i++) {
                float x = i * 100.0f;
                float y = 0;
                enemies.push_back(Enemy(x, y));
            }
        }
        else if (pattern == 1) {
            for (int i = 0; i < 5; i++) {
                float x;
                if (i == 0) {
                    x = 100.0f;
                }
                else if (i == 1)
                    x = 250.0f;
                else if (i == 4)
                    x = 600.0f;
                else
                    x = 150 + i * 100.0f;
                float y = 0;
                enemies.push_back(Enemy(x, y));
            }
        }
        else {
            for (int i = 0; i < 2; i++) {
                float x;
                if (i == 0) {
                    x = 250.0f;
                }
                else
                    x = 450.0f;
                float y = 0;
                enemies.push_back(Enemy(x, y));
            }
        }
    }

    int getEnemyCount() {
        return enemies.size();
    }
};

bool collisionCheck(Bullet& bullet, Player& player, EnemyManager& enemyManager) {
    if (bullet.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        return true;
    }

    for (auto& enemy : enemyManager.enemies) {
        if (bullet.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
            if (!bullet.enemyBullet) {
                enemy.handleBulletHit();
            }
            bullet.markForRemoval = true;

            if (enemy.hitCount == 1) {
                player.score += 10;
            }
            else if (enemy.hitCount == 2) {
                player.score += 10;
            }
            else if (enemy.hitCount == 3) {
                player.score += 10;
            }
        }
    }

    for (auto& enemy : enemyManager.enemies) {
        if (player.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

bool gameUpdate(Player& player, EnemyManager& enemyManager) {
    for (int i = 0; i < player.bullets.size(); i++) {
        player.bullets[i].update();
        if (collisionCheck(player.bullets[i], player, enemyManager)) {
            return true;
        }
        else if (player.bullets[i].shape.getPosition().y < 0) {
            player.bullets[i] = player.bullets.back();
            player.bullets.pop_back();
            i--;
        }
    }

    for (auto& enemy : enemyManager.enemies) {
        enemy.update();
        if (enemy.markForRemoval) {
            enemy = enemyManager.enemies.back();
            enemyManager.enemies.pop_back();
        }
        for (int i = 0; i < enemy.enemyBullets.size(); i++) {
            enemy.enemyBullets[i].update();
            if (collisionCheck(enemy.enemyBullets[i], player, enemyManager)) {
                return true;
            }
            else if (enemy.enemyBullets[i].shape.getPosition().y > 800) {
                enemy.enemyBullets[i] = enemy.enemyBullets.back();
                enemy.enemyBullets.pop_back();
                i--;
            }
        }

        if (enemy.shape.getPosition().y > 750) {
            return true;
        }
    }

    return false;
}

class Game {
public:
    Game() : window(sf::VideoMode(750, 800), "SFML Window"), player(), orb(), enemyManager(), frameCounter(0), score(0) {
        srand(time(NULL));

        if (!FONT.loadFromFile("arial.ttf")) {
            // error
        }

        scoreText.setFont(FONT);
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(TEXTCOLOR);
        scoreText.setPosition(650, 10);
        updateScoreText();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            handleInput();
            update();
            render();
            sf::sleep(sf::milliseconds(25));
        }
    }

private:
    sf::RenderWindow window;
    Player player;
    Orb orb;
    EnemyManager enemyManager;
    int frameCounter;
    int score;
    sf::Text scoreText;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.moveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player.shoot();
            player.shot = true;
        }
        else {
            player.shot = false;
        }
    }

    void update() {
        player.update();

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
        }
    }

    void spawnAdditionalEnemies() {
        int pattern = rand() % 3;

        if (pattern == 0) {
            for (int i = 1; i < 7; i++) {
                float x = i * 100.0f;
                float y = 0;
                enemyManager.enemies.push_back(Enemy(x, y));
            }
        }
        else if (pattern == 1) {
            for (int i = 0; i < 5; i++) {
                float x;
                if (i == 0) {
                    x = 100.0f;
                }
                else if (i == 1)
                    x = 250.0f;
                else if (i == 4)
                    x = 600.0f;
                else
                    x = 150 + i * 100.0f;
                float y = 0;
                enemyManager.enemies.push_back(Enemy(x, y));
            }
        }
        else {
            for (int i = 0; i < 2; i++) {
                float x;
                if (i == 0) {
                    x = 250.0f;
                }
                else
                    x = 450.0f;
                float y = 0;
                enemyManager.enemies.push_back(Enemy(x, y));
            }
        }
    }

    void render() {
        window.clear();

        window.draw(player.shape);

        for (auto& enemy : enemyManager.enemies) {
            window.draw(enemy.shape);
            for (auto& enemyBullet : enemy.enemyBullets) {
                window.draw(enemyBullet.shape);
            }
        }

        window.draw(orb.shape);

        for (auto& bullet : player.bullets) {
            if (bullet.markForRemoval) {
                bullet = player.bullets.back();
                player.bullets.pop_back();
            }
        }

        for (auto& i : player.bullets) {
            window.draw(i.shape);
        }

        window.draw(scoreText);

        window.display();
    }

    void updateScoreText() {
        scoreText.setString("Score: " + std::to_string(score));
    }
};

int main() {
    Game game;
    game.run();
}