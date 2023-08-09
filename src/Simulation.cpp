#include "../include/Simulation.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

Simulation::~Simulation()
{
    m_grid.deleteGridMap();
}

Simulation::Simulation()
{
    m_objects.reserve(10000);
    initText();
    
}

const void Simulation::setWindow( sf::RenderWindow& window )
{
    m_window = &window;
    m_grid.initGrid(m_ballRad * 2, *m_window);
}
const void Simulation::setSubSteps( int substeps )
{
    m_subStepNumber = substeps;
}
const float Simulation::getSubDeltaTime( ) const
{
    return m_deltaTime / static_cast<float>(m_subStepNumber);
}
const int Simulation::getSubSteps( ) const
{
    return m_subStepNumber;
}

const float Simulation::getTime() const
{
    return m_time;
}

Object& Simulation::addNewObject( sf::Vector2f startPos, float r, bool pinned )
{
    return m_objects.emplace_back(startPos, r, m_objects.size(), pinned); 
}

void Simulation::initText()
{
    if(!m_font.loadFromFile("../res/fonts/open-sans/OpenSans-Semibold.ttf"))
    {
        std::cout << "ERROR LOADING FILE IN SIMULATION CLASS" << '\n';
    }

    m_debugText.setFillColor(sf::Color::White);
    m_debugText.setFont(m_font);
    m_debugText.setCharacterSize(20);
    m_debugText.setPosition(10,10);
    m_debugText.setString("NULL");
}


void Simulation::setDeltaTime()
{
     m_deltaTime = m_deltaTimeClock.restart().asSeconds() * MULT;
}
// UPDATING
void Simulation::updateText()
{
    std::stringstream ss;
    ss << "FPS: " << static_cast<unsigned>(Time::getFps())<<'\n'
        << "SIM TIME: " << m_simUpdateClock.restart().asMilliseconds() << "ms" << '\n'
        << "BALLS: " << m_objects.size() << '\n'
        ;
    m_debugText.setString(ss.str());
}

void Simulation::getInput()
{
    if(InputHandler::isLeftMouseClicked())
    {
        if(mouseHoveringBall())
            m_grabbingBall = true;

    }
    else {
        m_grabbingBall = false;
        for(auto &obj : m_objects)
        {
            if(obj.isGrabbed)
            {
                obj.isGrabbed = false;
                obj.outlineThic = 0;
                obj.addVelocity(m_mouseVelocity, getSubDeltaTime());

            }

        }
    }


    if(InputHandler::isCClicked())
    {
        if(!m_isKeyHeld)
        {
            m_isKeyHeld = true;
            m_objects.clear();
        }

    }
    else{
        m_isKeyHeld = false;
    }
}

void Simulation::updateMousePos()
{
    m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
}

void Simulation::calcMouseVelocity()
{
    // useful so that when grabbing a ball, then letting go, depending on how you throw the mouse, depends on how the ball is thrown
    m_mouseVelocity = m_mousePosView - m_mouseOldPos;
    m_mouseOldPos = m_mousePosView;
}

void Simulation::update( )
{
    setDeltaTime();
    m_time+= m_deltaTime;
    updateText();
    getInput();
    updateMousePos();
    calcMouseVelocity();
    float subStepDT = getSubDeltaTime();
    for(int i{getSubSteps()}; i > 0; --i)
    {
        demoSpawner();
        checkConstraints();
        checkCollisions();
        updateObjects( subStepDT );
        applyGravityToObjects();
        ballGrabbedMovement();
    }
    m_grid.clearGrid();


}

bool Simulation::mouseHoveringBall()
{
    for(auto &obj: m_objects)
    {
        sf::Vector2f axis = m_mousePosView - obj.currentPos;
        float dist = sqrt(axis.x * axis.x + axis.y * axis.y);
        
        if(dist < obj.radius && !m_grabbingBall)
        {
            obj.isGrabbed = true;
            obj.outlineThic = 1;
            return true;
        }
    }

    return false;
}

void Simulation::ballGrabbedMovement()
{
    for(auto &obj : m_objects)
    {
        if(obj.isGrabbed)
        {
            obj.outlineThic = 1;
            obj.currentPos = m_mousePosView;
        }
    }
}

sf::Color Simulation::getRainbowColors( float time )
{
    float red = sin(time);
    float green = sin(time + 0.3f * 2);
    float blue = sin(time + 0.6f * 2.0);


    return sf::Color( 
        static_cast<unsigned>(red * red * 255),
        static_cast<unsigned>(green * green * 255),
        static_cast<unsigned>(blue * blue * 255)
            );
}

void Simulation::demoSpawner()
{
    sf::Vector2f spawnPos = {m_window->getSize().x * 0.5f, m_window->getSize().y * 0.25f};
    int maxBalls = 100;
    float spawnDelay = 0.1f;
    float spawnSpeed = 50;

    if(m_objects.size() < maxBalls && m_clock.getElapsedTime().asSeconds() >= spawnDelay)
    {
        m_clock.restart().asSeconds();
        Object& ob = addNewObject(spawnPos, m_ballRad);
        ob.addVelocity(sf::Vector2f(10,1), getSubDeltaTime());
        ob.color = getRainbowColors(m_time);

    }

}

void Simulation::checkConstraints()
{
    for(auto &obj : m_objects)
    {
        float winWidth = m_window->getSize().x;
        float winHeight = m_window->getSize().y;
        sf::Vector2f veloc = obj.currentPos - obj.oldPos;
        if(obj.currentPos.x > winWidth - obj.radius)
        {
            obj.currentPos.x = winWidth - obj.radius;
            obj.oldPos.x = obj.currentPos.x + veloc.x * obj.friction;
        }
        if(obj.currentPos.x < obj.radius)
        {
            obj.currentPos.x = obj.radius;
            obj.oldPos.x = obj.currentPos.x + veloc.x * obj.friction;
        }
        if(obj.currentPos.y < obj.radius)
        {
            obj.currentPos.y = obj.radius;
            // obj.oldPos.y = obj.currentPos.y + veloc.y * obj.friction;
        }
        if(obj.currentPos.y > winHeight - obj.radius)
        {
            obj.currentPos.y = winHeight - obj.radius;
            // obj.oldPos.y = obj.currentPos.y + veloc.y * obj.friction;
        }
    }
}

void Simulation::checkCollisions()
{
    for(int x{1}; x < m_grid.getWidth()- 1; ++x)
    {
        for(int y{1}; y < m_grid.getHeight() -1; ++y)
        {
            std::vector<int>& indxs1 = m_grid.getIndexesAtPos(x,y);
            for(int dx{-1}; dx <= 1; ++dx)
            {
                for(int dy{-1}; dy <= 1; ++dy)
                {
                    std::vector<int>& indxs2 = m_grid.getIndexesAtPos(x + dx, y + dy);

                    // cheking the cols

                    for(int i = 0; i < indxs1.size(); ++i)
                    {
                       for(int j = 0; j < indxs2.size(); ++ j)
                       {
                            if(i != j)
                            {
                                Object& obj1 = m_objects[i];
                                Object& obj2 = m_objects[j];

                                sf::Vector2f axis = obj1.currentPos - obj2.currentPos;
                                float distance = sqrt(axis.x * axis.x + axis.y * axis.y);
                                float minAllowedDist = obj1.radius + obj2.radius;
                                if(distance < minAllowedDist)
                                {
                                    float moveAmount = minAllowedDist - distance;
                                    float perc = (moveAmount / distance) * 0.5f;
                                    sf::Vector2f off = axis * perc;

                                    if(!obj1.isPinned)
                                        obj1.currentPos+= off;
                                    if(!obj2.isPinned)
                                        obj2.currentPos -= off;
                                }

                            }
                       }
                    }

                }
            }
        }
    }

    /*
    for(std::size_t i = 0; i < m_objects.size(); ++i)
    {
        Object& obj1 = m_objects[i];
        for(std::size_t j = i + 1; j < m_objects.size(); ++j)
        {
            Object& obj2 = m_objects[j];
            sf::Vector2f axis = obj1.currentPos - obj2.currentPos;
            float distanceBtw = sqrt(axis.x * axis.x + axis.y * axis.y);
            float minAllowedDist = obj1.radius + obj2.radius;
            if(distanceBtw < minAllowedDist)
            {
                float moveAmount = minAllowedDist - distanceBtw;
                float percentage = (moveAmount / distanceBtw) * 0.5;
                sf::Vector2f offsetAmount = axis * percentage;

                if(!obj1.isPinned)
                    obj1.currentPos += offsetAmount;
                if(!obj2.isPinned)
                    obj2.currentPos -= offsetAmount;
            }
        }
    }
    */
}

void Simulation::updateObjects( float subDeltaTime )
{
    for( auto &obj : m_objects)
    {
        obj.update(subDeltaTime);
        int posx = obj.currentPos.x / m_grid.getGridSize();
        int posy = obj.currentPos.y / m_grid.getGridSize();


        m_grid.setIndexAtPos(posx, posy, obj.ID);
    }
}

void Simulation::applyGravityToObjects( )
{
    for(auto &obj : m_objects)
    {
        obj.accelerate( obj.mass * GRAVITY);
    }
}


// RENDERING
void Simulation::render( sf::RenderTarget &target )
{
    /*
    sf::RectangleShape shape;
    for(int x = 0; x < m_grid.getWidth(); ++x)
    {
        for(int y = 0; y < m_grid.getHeight(); ++y)
        {
            shape.setFillColor(sf::Color::Black);
            shape.setPosition(sf::Vector2f(x * m_grid.getGridSize(), y * m_grid.getGridSize()));
            shape.setSize(sf::Vector2f(m_grid.getGridSize(), m_grid.getGridSize()));
            shape.setOutlineThickness(1);
            shape.setOutlineColor(sf::Color::White);

            target.draw(shape);
        }
    }
    */

    sf::CircleShape circleS;
    circleS.setPointCount(50);
    for(auto &obj : m_objects)
    {
        circleS.setRadius(obj.radius);
        circleS.setOrigin(obj.radius, obj.radius);
        circleS.setFillColor(obj.color);
        circleS.setPosition(obj.currentPos);
        circleS.setOutlineColor(obj.outlineColor);
        circleS.setOutlineThickness(obj.outlineThic);

        target.draw(circleS);
    }
}

void Simulation::renderUI( sf::RenderTarget &target )
{
    target.draw(m_debugText);
}
