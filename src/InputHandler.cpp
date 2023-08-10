#include "../include/InputHandler.h"
#include "SFML/System/Err.hpp"
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

bool InputHandler::isSpaceClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

bool InputHandler::isGClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::G);
}

bool InputHandler::isMiddleMouseClicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
}
