#include<iostream>
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Window.hpp"
#include "../include/Game.h"



sf::Window IGNORE(sf::VideoMode(0,0), "", sf::Style::None);

int main()
{
    std::srand(static_cast<unsigned>(time(nullptr)));

    Game game;
    game.startGLoop();
    return 0;
}
