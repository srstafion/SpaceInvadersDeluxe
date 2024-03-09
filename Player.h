#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Bullet.h"
#include <vector>
using namespace sf;
using namespace std;

class Player {
private:
    RectangleShape player;
    Texture playerT;
    RectangleShape mask1;
    RectangleShape mask2;

    vector<Bullet> bullets;
    Clock shootCountdown;

    SoundBuffer buffer;
    Sound sound;

    bool canShoot = true;
public:
    Player();

    void movePlayer(int direction);

    void shoot();

    Vector2f getPosition();

    FloatRect getMaskOneBounds();

    FloatRect getMaskTwoBounds();

    vector<Bullet>& getBullets();

    void updateBullets();

    void toggleShot(int toggle);

    void deleteBullet(int index);

    void show(RenderWindow& window);
};