#include "Bullet.h"

Bullet::Bullet(Vector2f position, int side) {
    bullet.setSize(Vector2f(5, 15));
    bullet.setPosition(position);
    bulletT.loadFromFile("./Textures/enemyBullet.png");
    bullet.setTexture(&bulletT);
    //if (side == 0) bullet.setFillColor(Color(255, 0, 0, 240));
    //else bullet.setFillColor(Color(255, 0, 255, 240));
}

void Bullet::moveBullet(int amount)
{
    bullet.move(0, amount);
}

Vector2f Bullet::getPosition()
{
    return bullet.getPosition();
}

FloatRect Bullet::getGlobalBounds()
{
    return bullet.getGlobalBounds();
}

void Bullet::showBullet(RenderWindow& window)
{
    window.draw(bullet);
}
Texture Bullet::bulletT;