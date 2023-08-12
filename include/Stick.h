#ifndef STICK_H
#define STICK_H
#pragma once
#include <_types/_uint8_t.h>
#include <cmath>
#include "Object.h"

struct Stick
{
    Object* obj1Ptr;
    Object* obj2Ptr;
    
    uint8_t ID;
    float length;

    Stick( Object& obj1, Object& obj2, float length, uint8_t ID);
    void update( );

    Object* getObject1( );
    Object* getObject2( );

    void resetObjectReferences( Object& obj1, Object& obj2 );

};


#endif //! STICK_H
