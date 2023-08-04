#ifndef TIME_H
#pragma once

#include <SFML/System/Clock.hpp>
#include "../include/Time.h"
#include "Global.h"

class Time{
    public:
        inline static float deltaTime;
        static void initDeltaTime();
        static void updateFPS();
        static float& getFps();
        
    private:
        inline static sf::Clock clock;
        inline static sf::Clock fpsClock;
        inline static sf::Time fpsTime;
        inline static float fps;
        static constexpr float MULTIPLIER = TIME_DELTATIME_MULT;;

};

#endif // !TIME_H
