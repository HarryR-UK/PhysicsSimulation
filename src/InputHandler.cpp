#include "../include/InputHandler.h"
#include "SFML/Window/Mouse.hpp"


bool InputHandler::isLeftMouseClicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool InputHandler::isRightMouseClicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
} 
