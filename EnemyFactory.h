#pragma once
#include "Header.h"
#include "Enemy.h"

class EnemyFactory {
private:
    vector<Enemy> enemies;
    SoundBuffer hitHurtB;
    Sound hitHurt;
    SoundBuffer explodeB;
    Sound explode;
public:
    EnemyFactory();

    void addRow();

    void show(RenderWindow& window);

    void updateEnemy();

    void deleteEnemy(int index);

    void handleBulletHit(int index);

    vector<Enemy> getEnemies();
};