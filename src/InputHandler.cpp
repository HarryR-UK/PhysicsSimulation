#include "../include/InputHandler.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"


bool InputHandler::isLeftMouseClicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool InputHandler::isRightMouseClicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
} 

bool InputHandler::isCClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
}
