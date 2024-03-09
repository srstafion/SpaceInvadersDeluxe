#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;

class Bullet {
private:
    RectangleShape bullet;
    static Texture bulletT;
public:
    Bullet(Vector2f position, int side);

    void moveBullet(int amount);

    Vector2f getPosition();

    FloatRect getGlobalBounds();

    void showBullet(RenderWindow& window);
};