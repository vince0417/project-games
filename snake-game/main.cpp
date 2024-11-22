#include "snake.hpp"

int main()
{
    Snake * snake = new Snake();
    snake->run_game();
    delete snake;
    snake = nullptr;
    return EXIT_SUCCESS;
}
