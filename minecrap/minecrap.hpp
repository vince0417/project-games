#ifndef MINECRAP_H
#define MINECRAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>
#include <iostream>

class Minecrap
{
    public:
        Minecrap();

        sf::RenderWindow window;
        // MUSICA E SONOPLASTIA(EFEITOS DE SOM OU FX)
        sf::SoundBuffer pop, gameover_buffer;
        sf::Sound pop_sound, gameover_sound;
        sf::Music music;

        bool pressed, gameover, paused;
        int points, health;
        float velocity, x, obj_vel_max, obj_vel = obj_vel_max ;

        sf::Font font, jet;
        sf::Text score, life, gameover_text, f1, paused_text;

        sf::Texture texture, bg, hammer, stop;


        sf::Sprite object, fundo, ham, stop_sprite;

        sf::Vector2i pos_mouse_win; //Posição do mouse em relação a janela(window)
        sf::Vector2f pos_mouse_coords; // Armazenará as coordenadas mapeadas

        // OBJETOS 
        std::vector<sf::Sprite> objs;
        size_t max_objs;

        void code_game();
        void game_over();
        void pause_game();
        void loop_events();
        void run_game();

};


#endif