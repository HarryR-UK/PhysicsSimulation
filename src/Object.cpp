#include "../include/Object.h"


Object::Object( sf::Vector2f startPos, float r, int id, bool pinned )
    : currentPos { startPos }
    , oldPos { startPos }
    , radius { r }
    , ID { id }
    , isPinned { pinned } 
    , acceleration { 0.f, 0.f } 
    , mass { radius / 100 }
{

}

void Object::update( float deltaTime )
{
    sf::Vector2f vel = currentPos - oldPos;
    oldPos = currentPos;

    currentPos = currentPos + vel + acceleration * ( deltaTime * deltaTime );

    acceleration = {0.f,0.f};


}

void Object::setVelocity(sf::Vector2f vel, float deltaTime)
{
    oldPos = currentPos - ( vel * deltaTime );
}

void Object::addVelocity( sf::Vector2f vel, float deltaTime )
{
    oldPos -= vel * deltaTime;
}

const sf::Vector2f Object::getVelocity( float deltaTime ) const
{
    return ( currentPos - oldPos ) / deltaTime;
}

void Object::accelerate( sf::Vector2f acc )
{
    acceleration += acc;
}

void Object::togglePinned()
{
    isPinned = !isPinned;
}
