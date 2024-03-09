#pragma once
#include "Header.h"
#include "Bullet.h"

class Enemy {
private:
    RectangleShape enemy;
    static Texture enemyT;
    Clock shootCooldown;
    vector<Bullet> bullets;
    int hitCount = 0;
    static SoundBuffer shootB;
    static Sound shootS;
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

    void moveBullets();

    void show(RenderWindow& window);
};