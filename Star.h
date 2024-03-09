#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "Header.h"

class Star {
private:
    RectangleShape star;
    static Texture starT;
    Clock clock;
    bool waiting = true;
public:
    Star();

    void commenceMovement();

    void draw(RenderWindow& window);
};