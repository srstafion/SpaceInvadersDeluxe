#include "Enemy.h"

Enemy::Enemy(Vector2f position)
{
    enemy.setSize(Vector2f(75, 75));
    enemy.setPosition(position);
    shootCooldown.restart();
    enemyT.loadFromFile("./Textures/edefault.png");
    enemy.setTexture(&enemyT);
    shootB.loadFromFile("./Sounds/laserShootEnemy.wav");
    shootS.setBuffer(shootB);
}

void Enemy::moveEnemy()
{
    enemy.move(0, 1);
}

void Enemy::update()
{
    moveEnemy();
    shoot();
    moveBullets();
    for (auto i = bullets.begin(); i != bullets.end(); ) {
        if (i->getPosition().y > 800) {
            i = bullets.erase(i);
        }
        else {
            i++;
        }
    }
    if (hitCount == 1) enemy.setFillColor(Color::Yellow);
    else if (hitCount == 2) enemy.setFillColor(Color::Green);
}

Vector2f Enemy::getPosition()
{
    return enemy.getPosition();
}

FloatRect Enemy::getGlobalBounds()

{
    return enemy.getGlobalBounds();
}

vector<Bullet> Enemy::getBullets()
{
    return bullets;
}

int Enemy::getHits()
{
    return hitCount;
}

void Enemy::setHits(int hits)
{
    hitCount = hits;
}

void Enemy::shoot()
{
    if (random(1, 1000) < 4) {
        Bullet bullet(Vector2f(enemy.getPosition().x + enemy.getSize().x / 2,
            enemy.getPosition().y + enemy.getSize().y), 1);
        bullets.push_back(bullet);
        shootS.play();
    }
}

void Enemy::moveBullets()
{
    for (auto& bullet : bullets) {
        bullet.moveBullet(7);
    }
}

void Enemy::show(RenderWindow& window)
{
    window.draw(enemy);
}
Texture Enemy::enemyT;
SoundBuffer Enemy::shootB;
Sound Enemy::shootS;