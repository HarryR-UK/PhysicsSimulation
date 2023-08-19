#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once
#include "Simulation.h"

#include <iostream>
#include <vector>

#include "SFML/Window/ContextSettings.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Application
{
    private:
        sf::RenderWindow* m_window;
        sf::ContextSettings m_contextSettings;
        sf::VideoMode m_videoMode;

        sf::Event m_event;
        sf::Cursor m_cursor;


        // Screen Info
        int m_screenWidth;
        int m_screenHeight;

        bool m_isKeyHeld = false;
        bool m_isFullScreen = false;


        // FONT
        sf::Font m_mainFont;

        // Mouse Pos
        sf::Vector2i m_mousePosScreen;
        sf::Vector2i m_mousePosWindow;

        pe::Simulation m_sim;

    private:
        void initVariables( );
        void initWindow( );
        void initFont( );
        void initText( );
        void toggleFullscreen( );


        

    public:
        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;

    public:

        Application( );
        virtual ~Application( );

        void run( );

        void update( );
        void updateMousePos( );

        void pollEvents( );
        void getInput( );

        void render( );


        const bool isRunning( ) const;



        // Accessors
        sf::RenderWindow* getWindow( );


};


#endif
