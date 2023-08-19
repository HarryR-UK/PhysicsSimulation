#ifndef STICKMAKER_H
#define STICKMAKER_H
#include "Object.h"
#include <vector>
#pragma once
#include "SFML/Graphics.hpp"

namespace Builder
{
    struct BluePrintStick
    {
        sf::CircleShape shape;
        bool isPinned;
    };
    

    struct StickMaker
    {
        std::vector<BluePrintStick> bluePrintSticks = {};
        bool finishedStick = true;


    };
};

#endif //!STICKMAKER_H
