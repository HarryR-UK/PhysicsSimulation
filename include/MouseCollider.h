#ifndef MOUSECOLLDER_H
#define MOUSECOLLDER_H
#pragma once
#include "SFML/Graphics.hpp"
namespace Builder {
    struct MouseCollider {
        float colliderRadius = 15;
        bool isColliderActive = false;
        sf::CircleShape colliderShape;

        // constaints
        float colliderMinRad = 1;
        float colliderMaxRad = 300;
        void constrainRadius();
        MouseCollider();


    };

}


#endif
