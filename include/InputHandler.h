#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#pragma once
#include <SFML/Graphics.hpp>

namespace handler {
    class InputHandler
    {
        private:

        public:
            static bool isLeftMouseClicked();
            static bool isRightMouseClicked();
            static bool isMiddleMouseClicked();

            static bool isSpaceClicked();
            static bool isEnterClicked();

            static bool isAClicked();
            static bool isCClicked();
            static bool isEClicked();
            static bool isFClicked();
            static bool isGClicked();
            static bool isPClicked();
            static bool isQClicked();
            static bool isSClicked();
            static bool isWClicked();

    };

}


#endif //!INPUTHANDLER_H
