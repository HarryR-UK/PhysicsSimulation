#ifndef SIMULATION_H
#define SIMULATION_H
#pragma once
#include <_types/_uint8_t.h>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include <sstream>

#include "IDVector.h"
#include "Global.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "Time.h"
#include "Object.h"
#include "InputHandler.h"
#include "Stick.h"
#include "StickMaker.h"
#include "Math.h"
#include "ColorHandler.h"
#include "gui/Button.h"

using namespace mth;
namespace pe {

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
            sf::Vector2f m_mouseVelocity;
            float m_mouseColRad = 15;
            bool m_mouseColActive = false;
            sf::CircleShape m_mouseColShape;

            float m_mouseColMaxRad = 300;
            float m_mouseColMinRad = 1;


            bool m_isKeyHeld = false;
            bool m_isMouseHeld = false;
            bool m_buildKeyHeld = false;

            bool m_gravityActive = true;
            bool m_paused = false;

            bool m_buildModeActive = false;
            bool m_newBallPin = false;

            const int MAXBALLS = 1000;

            sf::Clock m_spawnClock;
            float m_spawnNewBallDelay = 0.15;
            float m_spawnNewBluePrintDelay = 0.4f;

            IDVector<Object> m_objects;
            IDVector<Stick> m_sticks;

            Builder::StickMaker m_stickMaker;

            bool m_gotFirstBallToJoin = false;
            int m_obj1LinkID;
            int m_obj2LinkID;

            static const int s_ballPointCount = 30;

            int m_constraintWidth = 100;
            int m_constraintHeight = 100;


        private:
            void initText( );

            void updateObjects( float subDeltaTime );
            void updateSticks( );
            void updateText( );
            void updateMousePos( );

            void applyGravityToObjects( );

            void checkConstraints( );

            void checkCollisions( );
            void mouseCollisionsBall( );
            void getInput( );


            void ballGrabbedMovement( );

            bool mouseHoveringBall( );
            bool mouseHoveringBall( int& deleteID );

            void calcMouseVelocity( );
            void setDeltaTime( );

            void nonBuildModeMouseControls();
            void buildModeMouseControls();

        public:

        public:
            Simulation();
            ~Simulation();

            void initSticks( );

            void render( sf::RenderTarget& target );
            void renderSticks( sf::RenderTarget& target );
            void renderUI( sf::RenderTarget& target );
            void renderBluePrints( sf::RenderTarget& target );

            void deleteBall( int& delID );

            void startSim( );
            void simulate( );

            void demoSpawner( );

            Object& addNewObject( sf::Vector2f startPos, float r, bool pinned = false);
            Stick& addNewStick( int id1, int id2, float length );
            void makeStickChain( );
            void spawnStick( );
            void createJoint( );
            void clearEverything( );

            void togglePause( );
            void toggleGravity( );


            void changeMouseRadius( float change );

            const void setWindow( sf::RenderWindow& window );
            const void setSubSteps( int substeps );
            const void setConstraintDimensions( int w, int h);

            const float getSubDeltaTime( ) const;
            const int getSubSteps( ) const;
            const float getTime( ) const;
            IDVector<Object>& getObjects( );
            IDVector<Stick>& getSticks( );

    };

};

#endif // !DEBUG
