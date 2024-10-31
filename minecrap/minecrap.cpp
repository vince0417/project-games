#include "minecrap.hpp"

Minecrap::Minecrap(){
    // Window
    window.create(sf::VideoMode(1280,720), "Minecrap - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0,0));
    window.setMouseCursorVisible(false);

    // MUSICA E SONOPLASTIA(EFEITOS DE SOM OU FX)
    pop.loadFromFile("./assets/sound/pop.wav");
    gameover_buffer.loadFromFile("./assets/sound/game-over-sound.wav");
    pop_sound.setBuffer(pop);
    gameover_sound.setBuffer(gameover_buffer);
    music.openFromFile("./assets/sound/soundtrack.wav");

    pressed = false;
    gameover = false;
    paused = false;
    points = 0;
    health = 5;
    velocity = 3.f;

    font.loadFromFile("./assets/font/Minecraft.ttf");
    jet.loadFromFile("./assets/font/jetbrains.ttf");

    f1.setFont(jet);
    f1.setFillColor(sf::Color::Green);
    f1.setPosition(5,670);
    f1.setString("Pressione F1 para jogar novamente.");

    //paused
    paused_text.setFont(jet);
    paused_text.setFillColor(sf::Color::White);
    paused_text.setString("PAUSED");
    paused_text.setPosition(350,300);
    paused_text.setCharacterSize(150);


    //gamerover
    gameover_text.setFont(font);
    gameover_text.setFillColor(sf::Color::White);
    gameover_text.setString("GAME OVER");
    gameover_text.setPosition(350,300);
    gameover_text.setCharacterSize(100);

    //score
    score.setFont(font);
    score.setString("Pontos: " + std::to_string(points));
    score.setFillColor(sf::Color::Green);
    score.setPosition(5.f,5.f);

    //lifes
    life.setFont(font);
    life.setString("Vidas: " + std::to_string(health));
    life.setFillColor(sf::Color::Red);
    life.setPosition(1130.f,5.f);

    texture.loadFromFile("./assets/image/minecrap.png");
    bg.loadFromFile("./assets/image/fundo.jpg");
    hammer.loadFromFile("./assets/image/hammer.png");
    stop.loadFromFile("./assets/image/paused.jpg");

    object.setTexture(texture);
    fundo.setTexture(bg);
    ham.setTexture(hammer);
    stop_sprite.setTexture(stop);
    
    x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - texture.getSize().x)));
    object.setPosition(sf::Vector2f(10.f,10.f));


    // OBJETOS 
    max_objs = 5;
    obj_vel_max = 10.f;
    obj_vel = obj_vel_max;

}

void Minecrap::code_game()
{
    // Adiciona objects ao nosso vector com atrasos
    if (objs.size() < max_objs)
    {
        if (obj_vel >= obj_vel_max)
        {
            x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - texture.getSize().x)));
            object.setPosition(x,10.f);
            objs.push_back(object);
            obj_vel = 0.f;
        }else{
                obj_vel += 1.f;
        }
    }

    // Mover e deletar os objects do vector
    for (size_t i {}; i < objs.size(); i++)
    {
        bool del = false;
        objs[i].move(0.f,velocity);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
        {
            if (objs[i].getGlobalBounds().contains(pos_mouse_coords))
            {
                pop_sound.play();
                del = true;
                points += 10.f;
                score.setString("Pontos: " + std::to_string(points));
                pressed = true;
                if (points % 100 == 0)
                {
                    velocity += 0.1f;
                }
                if (points % 200 == 0)
                {
                    health++;
                }
                            
                            
            }
        }
        if (objs[i].getPosition().y > window.getSize().y)
        {
            --health;
            life.setString("Vidas: " + std::to_string(health));
            del = true;
            if (health <= 0)
            {
                gameover_sound.play();
                gameover = true;
            }
        } 

        if (del)
        {
            objs.erase(objs.begin() + i);
        }
                    
    }

    window.clear();
    window.draw(fundo);
    window.draw(life);
    window.draw(score);
    for (auto &e : objs)
    {
        window.draw(e);
    }
    window.draw(ham);
    window.display();
}

void Minecrap::game_over()
{
    music.stop();  
    window.setMouseCursorVisible(true);
    window.clear(sf::Color::Black);
    window.draw(score);
    window.draw(f1);
    window.draw(gameover_text);
    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
        objs.clear();
        health = 5;
        life.setString("Vidas: " + std::to_string(health));
        points = 0;
        score.setString("Pontos: " + std::to_string(points));
        gameover = false;
        velocity = 3.f;
        window.setMouseCursorVisible(false);
    }
}

void Minecrap::pause_game()
{
    music.pause();
    window.clear();
    window.draw(stop_sprite);
    window.draw(paused_text);
    window.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        paused = false;
    }
}

void Minecrap::loop_events()
{
    sf::Event event;
    if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused)
    {
        music.play();
    }
        
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect visible_area(0,0,event.size.width, event.size.height);
            window.setView(sf::View(visible_area));
        }
            
        if (event.type == event.MouseButtonPressed)
        {
            pressed = false;
        }
            
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            paused = true;
        }
            

        pos_mouse_win = sf::Mouse::getPosition(window);
        pos_mouse_coords = window.mapPixelToCoords(pos_mouse_win);
        ham.setPosition((sf::Vector2f)pos_mouse_win);
    }

}

void Minecrap::run_game()
{
    while (window.isOpen())
    {
        this->loop_events();
        if (gameover){  
            this->game_over();        
        }
        else{
            if (paused){  
                this->pause_game();  
            }
            else{
                this->code_game();
            }   
        } 
    } 
}
