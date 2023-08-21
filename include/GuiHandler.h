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
            pe::Simulation* m_sim = nullptr;

            sg::Button m_clearButton;
            sf::Font* m_font;

        private:
            void initButtons( );

        public:

        public:
            GuiHandler( pe::Simulation& sim );
            ~GuiHandler();
            void render( sf::RenderTarget& target );
            void update( );

    };


};

#endif
