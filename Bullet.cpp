#include "Bullet.h"

Bullet::Bullet(Vector2f position) {
    bullet.setFillColor(Color::Yellow);
    bullet.setSize(Vector2f(5, 15));
    bullet.setPosition(position);
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
