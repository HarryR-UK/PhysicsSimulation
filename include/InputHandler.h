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
        static bool isMiddleMouseClicked();

        static bool isSpaceClicked();
        static bool isEnterClicked();

        static bool isCClicked();
        static bool isEClicked();
        static bool isFClicked();
        static bool isGClicked();
        static bool isPClicked();
        static bool isQClicked();
        static bool isSClicked();

};


#endif //!INPUTHANDLER_H
