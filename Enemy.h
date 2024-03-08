#pragma once
#include "Header.h"
#include "Bullet.h"

class Enemy {
private:
    RectangleShape enemy;
    Texture enemyT;
    Clock shootCooldown;
    vector<Bullet> bullets;
    int hitCount = 0;
public:
    Enemy(Vector2f position);

    void moveEnemy();

    void update();

    Vector2f getPosition();

    FloatRect getGlobalBounds();

    vector<Bullet> getBullets();

    int getHits();

    void setHits(int hits);

    void shoot();

    void show(RenderWindow& window);
};