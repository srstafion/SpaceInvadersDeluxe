#include "Enemy.h"

Enemy::Enemy(Vector2f position)
{
    enemy.setFillColor(Color::Red);
    enemy.setSize(Vector2f(50, 50));
    enemy.setPosition(position);
    shootCooldown.restart();
}

void Enemy::moveEnemy()
{
    enemy.move(0, 1);
}

void Enemy::update()
{
    moveEnemy();
    shoot();
    for (auto i = bullets.begin(); i != bullets.end(); ) {
        if (i->getPosition().y > 800) {
            i = bullets.erase(i);
        }
        else {
            i++;
        }
    }
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
            enemy.getPosition().y + enemy.getSize().y));
        bullets.push_back(bullet);
    }
}

void Enemy::show(RenderWindow& window)
{
    window.draw(enemy);
}