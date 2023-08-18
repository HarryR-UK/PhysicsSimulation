#ifndef BUILDCONTROLLER_H
#define BUILDCONTROLLER_H
#pragma once

#include "SFML/Graphics.hpp"
#include "InputHandler.h"


namespace Builder {

    struct MouseCollider {
        float mouseColRadius = 15;
        bool isColliderActive = false;
        sf::CircleShape colliderShape;

        // constaints
        float colliderMinRad = 1;
        float colliderMaxRad = 300;
        MouseCollider();


    };

    class BuildController
    {
        private:
            bool m_isKeyHeld = false;
            bool m_isMouseHeld = false;
            bool m_isBuildKeyHeld = false;
            bool m_isBuildActive = false;

            bool* m_isPaused = nullptr;
            bool* m_isGravityActive = nullptr;
            bool* m_isNewBallPinned = nullptr;


        private:
            void buildModeControls( );
            void nonBuildModeControls( );

        public:

        public:
            void getInput( ); 
            MouseCollider mouseCollider;

            void setIsPaused(bool& paused);
            void setIsGravity(bool& gravity);
            void setIsNewBallPin(bool& ballPin);

    };

}

#endif // !BUILDCONTROLLER_H
