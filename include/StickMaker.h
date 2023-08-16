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
    
    struct IDHolder
    {
        int ID1;
        int ID2;
        float dist;

        IDHolder(int id1, int id2, float distance)
        {
            ID1 = id1;
            ID2 = id2; 
            dist = distance;
        }
    };

    struct StickMaker
    {
        std::vector<BluePrintStick> bluePrintSticks = {};
        bool finishedStick = true;
        std::vector<IDHolder> idHolder = {};


    };
};

#endif //!STICKMAKER_H
