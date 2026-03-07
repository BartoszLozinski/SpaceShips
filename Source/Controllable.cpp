#include "Headers/Controllable.hpp"

Controllable::Controllable(const Game::Vector2f& position_, const float rotation_, const Game::Vector2u& size_, const float maxSpeed_, const float speed_, const float rotationSpeed_)
    : Sprite(position_, rotation_, size_, maxSpeed_, speed_)
    , rotationSpeed(rotationSpeed_)
{}

/*
Controllable::Controllable(Game::Vector2u position, float rotation, float maxSpeed, float speed, float acceleration, float rotationSpeed)
    : Sprite(position, rotation, maxSpeed, speed)
    , acceleration_(acceleration)
    , rotationSpeed_(rotationSpeed)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(rotation);
}

Controllable::Controllable()
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(0.f);
}

Controllable::Controllable(Game::Vector2u position)
    : Moveable(position)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(0.f);
}
*/

void Controllable::accelerate()
{
    //speed up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and
       speed < maxSpeed)
    {
        if(speed >= maxSpeed - acceleration)
        {
            speed = maxSpeed;
        }
        else
        {
            speed += acceleration;
        }
    }
    //slow down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and
       speed > 0.f)
    {
        if(speed < acceleration)
        {
            speed = 0.f;
        }
        else
        {
            speed -= acceleration;
        }
    }
}

void Controllable::changeDirection()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        turnLeft();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        turnRight();
    }
}

void Controllable::turnLeft()
{
    sprite_.setRotation(sprite_.getRotation() - rotationSpeed);
}

void Controllable::turnRight()
{
    sprite_.setRotation(sprite_.getRotation() + rotationSpeed);
}

/*________________________GETTERS________________________________*/

float Controllable::getAcceleration() const
{
    return this->acceleration;
}

float Controllable::getRotationSpeed() const
{
    return this->rotationSpeed;
}

/*____________________SETTERS_________________________________*/

void Controllable::setAcceleration(float acceleration)
{
    this->acceleration = acceleration;
}

void Controllable::setRotationSpeed(float rotationSpeed)
{
    this->rotationSpeed = rotationSpeed;
}


