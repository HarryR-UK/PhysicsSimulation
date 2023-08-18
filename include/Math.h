#ifndef MATH_H
#define MATH_H
#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

namespace mth
{
    struct Math
    {
        constexpr static float PI = 3.14159265359;
        static float getDistance(sf::Vector2f& pos1, sf::Vector2f& pos2);
        static float deg2Rad(float& degrees);
        static float SOH_1(float& opposite, float& hypoteneuse);
        static sf::Vector2f getMouseVelocity(sf::Vector2f& mousePosView);

        private:
            static sf::Vector2f mouseOldPos;
    };
    
};


#endif // !MATH_H
