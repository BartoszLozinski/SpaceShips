#pragma once
#ifndef MOVEABLE
#define MOVEABLE

#include "Sprite.hpp"
#include <math.h>
#include <vector>

class Moveable : public Sprite
{
protected:  
    float maxSpeed_ = 6.f;
    float speed_ = 0.f;
        
public:
    Moveable();
    Moveable(sf::Vector2f position);
    Moveable(sf::Vector2f position, float rotation);
    Moveable(sf::Vector2f position, float rotation, float maxSpeed, float speed);
    Moveable(sf::Vector2f position, float rotation, sf::Vector2f size, float maxSpeed, float speed);

    virtual ~Moveable() = default;
    
    virtual void updatePosition();

    float getSpeed() const;

    void setSpeed(float newSpeed);

};

#endif

