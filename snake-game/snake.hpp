#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Snake
{
    public:
        Snake();
        int cols, lines, size, width, heigth, direction, num, points;
        sf::RenderWindow window;
        sf::Texture t1, t2, t3;
        sf::Sprite sp1, sp2, sp3;
        sf::Clock clock;
        sf::Font font;
        sf::Text text;

        float timer, delay;

        void run_game();
        void collision(); 
};
