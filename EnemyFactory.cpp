#include "EnemyFactory.h"

EnemyFactory::EnemyFactory()
{
    hitHurtB.loadFromFile("./Sounds/hitHurt.wav");
    hitHurt.setBuffer(hitHurtB);
    explodeB.loadFromFile("./Sounds/explosion.wav");
    explode.setBuffer(explodeB);
}

void EnemyFactory::addRow()
{
    int pattern = rand() % 3;
    switch (pattern) {
    case 0:
        for (int i = 1; i < 7; i++) {
            float x = i * 100.0f;
            enemies.push_back(Enemy(Vector2f(x, -50)));
        }
        break;
    case 1:
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
            enemies.push_back(Enemy(Vector2f(x, -50)));
        }
        break;
    case 2:
        for (int i = 0; i < 2; i++) {
            float x;
            if (i == 0) {
                x = 250.0f;
            }
            else
                x = 450.0f;
            enemies.push_back(Enemy(Vector2f(x, -50)));
        }
        break;
    }
}

void EnemyFactory::show(RenderWindow& window)
{
    for (auto i : enemies) {
        i.show(window);
    }
}

void EnemyFactory::updateEnemy()
{
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].update();
        if (enemies[i].getPosition().y > 800) {
            deleteEnemy(i);
        }
    }
}

void EnemyFactory::deleteEnemy(int index)
{
    enemies.erase(enemies.begin() + index);
}

void EnemyFactory::handleBulletHit(int index)
{
    Enemy& enemy = enemies[index];
    enemy.setHits(enemy.getHits() + 1);
    if (enemy.getHits() == 3) {
        deleteEnemy(index);
        explode.play();
    }
    else hitHurt.play();
}

vector<Enemy> EnemyFactory::getEnemies()
{
    return enemies;
}
