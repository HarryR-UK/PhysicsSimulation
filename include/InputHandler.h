#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#pragma once
#include <SFML/Graphics.hpp>

class InputHandler
{
    private:

    public:
        static bool isLeftMouseClicked();
        static bool isRightMouseClicked();
        static bool isCClicked();
        static bool isSpaceClicked();
        static bool isGClicked();
        static bool isPClicked();
        static bool isMiddleMouseClicked();
        static bool isFClicked();
        static bool isEClicked();
        static bool isQClicked();
};


#endif //!INPUTHANDLER_H
