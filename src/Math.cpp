#include "../include/Math.h"
using namespace mth;

sf::Vector2f Math::mouseOldPos = {100,100};

float Math::getDistance( sf::Vector2f &pos1, sf::Vector2f &pos2 )
{
    sf::Vector2f axis = pos2 - pos1;
    return sqrt(axis.x * axis.x + axis.y * axis.y);
}

float Math::deg2Rad( float &degrees )
{
    return degrees * Math::PI / 180;
}


float Math::SOH_1( float& opposite, float& hypoteneuse )
{
    return asin(opposite / hypoteneuse);
}
sf::Vector2f Math::getMouseVelocity(sf::Vector2f& mousePosView)
{
    sf::Vector2f mouseVel = mousePosView - mouseOldPos;
    mouseOldPos = mousePosView;

    return mouseVel;
}
