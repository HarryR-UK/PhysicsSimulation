#include "../include/InputHandler.h"


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

bool InputHandler::isFClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::F);
}

bool InputHandler::isEClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::E);
}
bool InputHandler::isQClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

bool InputHandler::isSClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

bool InputHandler::isEnterClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}
bool InputHandler::isAClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}
bool InputHandler::isWClicked()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}
