#ifndef BUILDCONTROLLER_H
#define BUILDCONTROLLER_H
#pragma once

#include "SFML/Graphics.hpp"
#include "InputHandler.h"
#include "Simulation.h"


namespace Builder {

    class BuildController
    {
        private:
            bool m_isKeyHeld = false;
            bool m_isMouseHeld = false;
            bool m_isBuildKeyHeld = false;
            bool m_isBuildActive = false;

            Simulation& m_sim;



        private:

        public:

        public:
            BuildController(Simulation& sim);
            void buildModeControls( );
            void nonBuildModeControls( );
            void getInput( );

            const bool getIsBuildMode() const;
            const void setIsBuildMode(bool& value);

    };

}

#endif // !BUILDCONTROLLER_H
