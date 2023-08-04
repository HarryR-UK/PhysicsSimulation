#include<iostream>

#include "../include/Game.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;
    game.startGLoop();
    return 0;
}
