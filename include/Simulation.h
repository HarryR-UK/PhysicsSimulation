#ifndef SIMULATION_H
#define SIMULATION_H
#include "Global.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include "SFML/Graphics/Text.hpp"
#include <sstream>
#include "SFML/System/Vector2.hpp"
#include "Time.h"
#include "Object.h"
#include "Grid.h"
#include "InputHandler.h"
#pragma once

class Simulation
{
    private:
        sf::RenderWindow* m_window;

        int m_subStepNumber;
        float m_deltaTime;
        float m_subDeltaTime;
        float m_time;

        sf::Text m_debugText;
        sf::Font m_font;

        std::vector<Object> m_objects = {};
        std::vector<Object*> m_ptrObjects = {};

        int m_ballRad = BALL_RADIUS;

        const sf::Vector2f GRAVITY = { 0.f, 20.f };

        sf::Clock m_clock;
        sf::Clock m_simUpdateClock;


        
        bool m_grabbingBall = true;


        sf::Clock m_deltaTimeClock;
        float MULT  = 60;

        std::thread m_updateThread;

        // MOUSE
        sf::Vector2f m_mousePosView;
        sf::Vector2f m_mouseOldPos;
        bool m_isMouseHeld = false;
        sf::Vector2f m_mouseVelocity;
        float m_mouseColRad = 15;
        bool m_mouseColActive = false;
        sf::CircleShape m_mouseColShape;

        float m_mouseColMaxRad = 200;
        float m_mouseColMinRad = 4;


        bool m_isKeyHeld = false;
        bool m_gravityActive = true;
        bool m_paused = false;



    private:
        void initText( );

        void updateObjects( float subDeltaTime );
        void updateText( );
        void updateMousePos( );

        void applyGravityToObjects( );

        void checkConstraints( );

        void checkCollisions( );
        void mouseCollisionsBall( );
        void getInput( );

        void demoSpawner( );

        void ballGrabbedMovement( );
        bool mouseHoveringBall( );

        void calcMouseVelocity( );
        void setDeltaTime( );

        sf::Color getRainbowColors( float time );
        void simulate( );

    public:

    public:
        Simulation();
        ~Simulation();

        void render( sf::RenderTarget& target );
        void renderUI( sf::RenderTarget& target );


        void startSim( );
        void updateUI( );

        Object& addNewObject( sf::Vector2f startPos, float r, bool pinned = false);
        void joinUpdateThread( );
        void changeMouseRadius( float change );

        const void setWindow( sf::RenderWindow& window );
        const void setSubSteps( int substeps );

        const float getSubDeltaTime( ) const;
        const int getSubSteps( ) const;
        const float getTime( ) const;


};

#endif // !DEBUG
