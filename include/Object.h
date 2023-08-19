#ifndef VERLETOBJECT_H
#define VERLETOBJECT_H
#pragma once

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

struct Object
{
    sf::Vector2f currentPos;
    sf::Vector2f oldPos;
    sf::Vector2f acceleration;

    sf::Color color = sf::Color::White;
    float radius = 8.f;
    float friction = 0.95f;
    float mass = radius / 5.f;
    int ID;
    int outlineThic = 0;
    sf::Color outlineColor = sf::Color::White;

    bool isPinned = false;
    bool isGrabbed = false;
    bool isSelected = false;

    float bounceAmount = 0.5f;


    void update( float deltaTime );
    void accelerate( sf::Vector2f acc );
    void setVelocity( sf::Vector2f vel, float deltaTime );
    void addVelocity( sf::Vector2f vel, float deltaTime );
    const sf::Vector2f getVelocity( float deltaTime ) const;
    void togglePinned( );

    Object( int id, sf::Vector2f startPos, float r, bool pinned = false );

};

#endif
