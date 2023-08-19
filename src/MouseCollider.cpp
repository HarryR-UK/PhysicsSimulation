#include "../include/MouseCollider.h"
using namespace Builder;

MouseCollider::MouseCollider()
{
    colliderShape.setRadius(colliderRadius);
    colliderShape.setPointCount(20);
    colliderShape.setFillColor(sf::Color::Transparent);
    colliderShape.setOutlineThickness(1);
    colliderShape.setOutlineColor(sf::Color::Red);
    
}
void MouseCollider::constrainRadius()
{
    
}

