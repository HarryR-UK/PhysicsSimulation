#include "../include/Simulation.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>

Simulation::~Simulation()
{

}

Simulation::Simulation()
{
    m_objects.reserve(10000);
    initText();
    
}

const void Simulation::setWindow( sf::RenderWindow& window )
{
    m_window = &window;
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


void Simulation::setDeltaTime(float fps)
{
     m_deltaTime = (1 / fps) * Time::MULTIPLIER;
}
// UPDATING
void Simulation::updateText()
{
    std::stringstream ss;
    ss << "FPS: " << static_cast<unsigned>(Time::getFps())<<'\n'
        << m_simUpdateClock.restart().asMilliseconds() << "ms" << '\n'
        ;
    m_debugText.setString(ss.str());
}

void Simulation::getInput()
{
    
}

void Simulation::update( )
{
    m_time+= m_deltaTime;
    updateText();
    getInput();
    float subStepDT = getSubDeltaTime();
    for(int i{getSubSteps()}; i > 0; --i)
    {
        demoSpawner();
        checkConstraints();
        checkCollisions();
        updateObjects( subStepDT );
        applyGravityToObjects();
    }
}

void Simulation::demoSpawner()
{
    sf::Vector2f spawnPos = {m_window->getSize().x * 0.5f, m_window->getSize().y * 0.5f};
    int maxBalls = 1000;
    float spawnDelay = 0.1f;
    float spawnSpeed = 50;
    float ballRad = 8;

    if(m_objects.size() < 1000 && m_clock.getElapsedTime().asSeconds() >= spawnDelay)
    {
        m_clock.restart().asSeconds();
        Object& ob = addNewObject(spawnPos, ballRad);
        ob.oldPos.x -= 0.05f;
        ob.color = sf::Color::Cyan;

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
            //obj.oldPos.x = obj.currentPos.x + veloc.x * obj.friction;
        }
        if(obj.currentPos.x < obj.radius)
        {
            obj.currentPos.x = obj.radius;
            // obj.oldPos.x = obj.currentPos.x + veloc.x * obj.friction;
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
}

void Simulation::updateObjects( float subDeltaTime )
{
    for( auto &obj : m_objects)
    {
        obj.update(subDeltaTime);
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
    sf::CircleShape circleS;
    circleS.setPointCount(50);
    for(auto &obj : m_objects)
    {
        circleS.setRadius(obj.radius);
        circleS.setOrigin(obj.radius, obj.radius);
        circleS.setFillColor(obj.color);
        circleS.setPosition(obj.currentPos);
        target.draw(circleS);
    }
}

void Simulation::renderUI( sf::RenderTarget &target )
{
    target.draw(m_debugText);
}
