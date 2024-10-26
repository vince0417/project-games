#include "minecrap.hpp"

int main ()
{
    Minecrap * minecrap = new Minecrap();
    minecrap->run_game();
    delete minecrap;
    minecrap = nullptr;
    return EXIT_SUCCESS;
}
