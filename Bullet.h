#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Bullet {
private:
    RectangleShape bullet;
public:
    Bullet(Vector2f position);

    void moveBullet(int amount);

    Vector2f getPosition();

    FloatRect getGlobalBounds();

    void showBullet(RenderWindow& window);
};