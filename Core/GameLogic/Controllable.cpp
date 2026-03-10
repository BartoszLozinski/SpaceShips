#include "Controllable.hpp"

namespace Game
{
    Controllable::Controllable(const Game::Vector2f& position_, const float rotation_, const Game::Vector2u& size_, const float maxSpeed_, const float speed_, const float rotationSpeed_)
        : Entity(position_, rotation_, size_, maxSpeed_, speed_)
        , rotationSpeed(rotationSpeed_)
    {}

    void Controllable::Accelerate()
    {
        if (speed >= maxSpeed - acceleration)
            speed = maxSpeed;
        else
            speed += acceleration;
    }

    void Controllable::Control(const ControlAction controlAction)
    {
        if (controlAction == ControlAction::Accelerate && speed < maxSpeed)
            Accelerate();
        else if (controlAction == ControlAction::SlowDown && speed > 0.f)
            SlowDown();

        if (controlAction == ControlAction::TurnLeft)
            TurnLeft();
        else if (controlAction == ControlAction::TurnRight)
            TurnRight();

    }

    void Controllable::SlowDown()
    {
        if (speed < acceleration)
            speed = 0.0f;
        else
            speed -= acceleration;
    };

    void Controllable::TurnLeft()
    {
        rotation -= rotationSpeed;
    }

    void Controllable::TurnRight()
    {
        rotation += rotationSpeed;
    }

    /*________________________GETTERS________________________________*/

    float Controllable::GetAcceleration() const
    {
        return acceleration;
    }

    float Controllable::GetRotationSpeed() const
    {
        return rotationSpeed;
    }

    /*____________________SETTERS_________________________________*/

    void Controllable::SetAcceleration(const float acceleration_)
    {
        acceleration = acceleration;
    }

    void Controllable::SetRotationSpeed(const float rotationSpeed_)
    {
        rotationSpeed = rotationSpeed;
    }



};

