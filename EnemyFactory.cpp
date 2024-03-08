#include "EnemyFactory.h"

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

void EnemyFactory::moveEn()
{
    for (auto& i : enemies) {
        i.moveEnemy();
    }
}

void EnemyFactory::updateEnemy()
{
    for (auto i : enemies) {
        if (i.getPosition().y > 800) {
            enemies.pop_back();
        }
    }
}

void EnemyFactory::deleteEnemy(int index)
{
    enemies.erase(enemies.begin() + index);
}

vector<Enemy> EnemyFactory::getEnemies()
{
    return enemies;
}
