#include "../include/Stick.h"

Stick::Stick( int stickID, int id1, int id2, float length )
{
    ID = stickID;
    obj1ID = id1;
    obj2ID = id2;
    this->length = length;
}

void Stick::update(Object &obj1, Object &obj2)
{
    sf::Vector2f axis = obj2.currentPos - obj1.currentPos;
    float distance = sqrt(axis.x * axis.x + axis.y * axis.y);
    float diff = length - distance;
    float perc = (diff / distance) * 0.5;
    sf::Vector2f offset = axis * perc;
    if(!obj1.isPinned)
        obj1.currentPos -= offset;
    if(!obj2.isPinned)
        obj2.currentPos += offset;
}
