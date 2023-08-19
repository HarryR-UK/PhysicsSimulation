#ifndef STICK_H
#define STICK_H
#pragma once
#include "Object.h"
#include <cmath>

struct Stick
{
    int obj1ID;
    int obj2ID;
    int ID;

    float length;

    Stick( int stickID, int id1, int id2, float length );

    // in simulation class, set object references based on the ID
    void update( Object& obj1, Object& obj2 );
};

#endif //!STICK_H
