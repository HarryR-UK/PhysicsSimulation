#ifndef GUIHANDLER_H
#define GUIHANDLER_H
#pragma once
#include "Simulation.h"
#include <vector>
#include "gui/Button.h"

namespace handler {
    class GuiHandler
    {
        private:
            sf::RenderWindow* m_window;
            pe::Simulation* m_sim = nullptr;
            sf::Font* m_font;
            sf::RectangleShape m_boundaryPole;
            int m_constraintWidth;
            int m_constraintHeight;

            sg::Button m_clearButton;
            sg::Button m_gravityButton;



        private:
            void initClearButton( );
            void initToggleGravityButton( );


        public:

        public:
            GuiHandler( pe::Simulation& sim );
            ~GuiHandler();
            void render( sf::RenderTarget& target );
            void update( );

            void initButtons( );

            const void setContraints(int w, int h);
            const void setWindow(sf::RenderWindow& window);
    };
};


#endif
