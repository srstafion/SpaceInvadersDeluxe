#include "Game.h"

//class Orb {
//public:
//    sf::RectangleShape shape;
//    bool active = false;
//
//    Orb() {
//        shape.setSize(sf::Vector2f(10, 10));
//        shape.setFillColor(sf::Color::Magenta);
//        shape.setPosition(random(0, 750 - 20), 800);
//    }
//
//    void update() {
//        if (active) {
//            shape.move(0, -0.2);
//            if (shape.getPosition().y > 800) {
//                active = false;
//                shape.setPosition(random(0, 750 - 20), 800);
//            }
//        }
//    }
//
//    bool checkCollision(Player& player) {
//        if (active && shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
//            active = false;  // Change this line
//            shape.setPosition(random(0, 750 - 20), 800);
//            return true;
//        }
//        return false;
//    }
//};

int main() {
    Game game;
    game.run();
}