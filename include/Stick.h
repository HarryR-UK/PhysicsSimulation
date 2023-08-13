#ifndef STICK_H
#define STICK_H
#pragma once
#include <_types/_uint8_t.h>
#include <cmath>
#include "Object.h"
#include <vector>

struct Stick
{
    Object* obj1Ptr = nullptr;
    Object* obj2Ptr = nullptr;
    std::vector<Object>* objectsRef;
    
    int ID;
    
    int objID1;
    int objID2;

    float length;

    bool isActive = true;

    Stick( Object* obj1, Object* obj2, float length, int ID );
    void update( );

    Object* getObject1( );
    Object* getObject2( );

    void resetObjectReferences( Object& obj1, Object& obj2 );

};


#endif //! STICK_H
