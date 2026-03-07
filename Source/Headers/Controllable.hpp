#pragma once
#ifndef CONTROLLABLE
#define CONTROLLABLE

#include "Moveable.hpp"
#include <vector>

class Controllable : public Moveable
{
protected:
    float acceleration_ = 0.1f;
    float rotationSpeed_ = 3.f; //deg
    sf::Vector2f velocity_{0.f, 0.f};
    
public:
    Controllable();
    Controllable(sf::Vector2f position);
    Controllable(sf::Vector2f position, float rotation, float maxSpeed, float speed, float acceleration, float rotationSpeed);
    Controllable(sf::Vector2f position, float rotation, sf::Vector2f size, float maxSpeed, float speed, float acceleration, float rotationSpeed);

    virtual ~Controllable() = default;
    
    void accelerate();
    void changeDirection();
    void turnLeft();
    void turnRight();

/*______________________GETTERS__________________________*/

    float getAcceleration() const;
    float getRotationSpeed() const;

/*_____________________SETTERS____________________________*/

    void setAcceleration(float acceleration);
    void setRotationSpeed(float rotationSpeed);

};

#endif

