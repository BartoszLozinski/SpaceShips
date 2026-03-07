#pragma once
#ifndef CONTROLLABLE
#define CONTROLLABLE

#include "Sprite.hpp"
#include <vector>

class Controllable : public Sprite
{
protected:
    float rotationSpeed = 3.f; //deg
    float acceleration = 0.2f;

    
public:
    /*
    Controllable();
    Controllable(Game::Vector2u position);
    Controllable(Game::Vector2u position, float rotation, float maxSpeed, float speed, float acceleration, float rotationSpeed);
    */
    Controllable(const Game::Vector2f& position_ = { 200.f, 300.f }, const float rotation_ = 0.f, const Game::Vector2u& size_ = { 30, 30 }, const float maxSpeed_ = 6.0f, const float speed_ = 0.f, const float rotationSpeed_ = 3.0f);

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

