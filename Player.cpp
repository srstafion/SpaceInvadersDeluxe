#include "Player.h"
#include <iostream>

Player::Player()
{
    player.setSize(Vector2f(75, 75));
    player.setPosition(250, 520);
    playerT.loadFromFile("./Textures/pdefault.png");
    player.setTexture(&playerT);
    shootCountdown.restart();
    buffer.loadFromFile("./Sounds/laserShoot.wav");
    sound.setBuffer(buffer);
}

void Player::movePlayer(int direction)
{
    switch (direction) {
    case 1:
        if (player.getPosition().y > 0) {
            player.move(0, -10);
        }
        break;
    case 2:
        if (player.getPosition().x > 0) {
            player.move(-10, 0);
        }
        break;
    case 3:
        if (player.getPosition().y < 725) {
            player.move(0, 10);
        }
        break;
    case 4:
        if (player.getPosition().x < 680) {
            player.move(10, 0);
        }
        break;
    }
}

void Player::shoot()
{
    if (canShoot) {
        Time elapsed = shootCountdown.getElapsedTime();
        if (elapsed.asMilliseconds() >= 150 || bullets.empty()) {
            Bullet bullet(Vector2f(player.getPosition().x + 35, player.getPosition().y));
            bullets.push_back(bullet);
            sound.play();
            shootCountdown.restart();
        }
    }
}

Vector2f Player::getPosition()
{
    return player.getPosition();
}

FloatRect Player::getGlobalBounds()
{
    return player.getGlobalBounds();
}

vector<Bullet>& Player::getBullets()
{
    return bullets;
}

void Player::updateBullets()
{
    for (auto& bullet : bullets) {
        bullet.moveBullet(-20);
    }
    for (auto i = bullets.begin(); i != bullets.end(); ) {
        if (i->getPosition().y <= 0) {
            i = bullets.erase(i);
        }
        else {
            i++;
        }
    }
}

void Player::toggleShot(int toggle)
{
    canShoot = toggle;
}

void Player::deleteBullet(int index)
{
    bullets.erase(bullets.begin() + index);
}

void Player::show(RenderWindow& window)
{
    window.draw(player);
}
