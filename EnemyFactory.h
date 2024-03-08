#pragma once
#include "Header.h"
#include "Enemy.h"

class EnemyFactory {
private:
    vector<Enemy> enemies;
public:
    EnemyFactory() {}

    void addRow();

    void show(RenderWindow& window);

    void moveEn();

    void updateEnemy();

    void deleteEnemy(int index);

    //void handleBulletHit() {
    //    hitCount++;
    //    switch (hitCount) {
    //    case 1:
    //        enemy.setFillColor(Color::Yellow);
    //        break;
    //    case 2:
    //        enemy.setFillColor(Color::Green);
    //        break;
    //    case3:
    //        /*markForRemoval = true;*/
    //    }
    //}

    vector<Enemy> getEnemies();
};