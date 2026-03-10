#pragma once

#include "Entity.hpp"
#include "ControlAction.hpp"

namespace Game
{
    class Controllable : public Entity
    {
    protected:
        float rotationSpeed = 3.f; //deg
        float acceleration = 0.2f;

        void Accelerate();
        void SlowDown();
        void TurnLeft();
        void TurnRight();

    public:
        Controllable(const Game::Vector2f& position_ = { 200.f, 300.f }, const float rotation_ = 0.f, const Game::Vector2u& size_ = { 30, 30 }, const float maxSpeed_ = 6.0f, const float speed_ = 0.f, const float rotationSpeed_ = 3.0f);
        virtual ~Controllable() = default;

        void Control(const ControlAction controlAction);
    /*______________________GETTERS__________________________*/

        float GetAcceleration() const;
        float GetRotationSpeed() const;

    /*_____________________SETTERS____________________________*/

        void SetAcceleration(const float acceleration_);
        void SetRotationSpeed(const float rotationSpeed_);

    };
};
