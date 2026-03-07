#pragma once

#include "Vector2t.hpp"


namespace Game
{
    class Entity
    {
    protected:
        int HP = 1;
        //position defined at the center of bounding box
        Vector2f position{ 200.f, 300.f };
        float rotation{};
        Vector2u size{ 30, 30 };
        Vector2f velocity{ 0.0f, 0.0f };

    public:
        Entity(const Vector2f& position_ = { 200.f, 300.f }, const float rotation_ = 0.f, const Vector2u& size_ = { 30, 30 });
        virtual ~Entity() = default;
        /*
        Entity(const Vector2u& position_, const float rotation_, const Vector2u& size_);
        Entity(const Vector2u& position_, const float rotation_);
        Entity(const Vector2u& position_);
        Entity() = default;
        */

        //Axis-Aligned Bounding Box for mid point origins
        [[nodiscard]] bool CheckCollision(const Entity& other) const;

        [[nodiscard]] int GetHP() const;
        [[nodiscard]] Vector2f GetPosition() const;
        [[nodiscard]] float GetRotation() const;
        [[nodiscard]] Vector2u GetSize() const;
        [[nodiscard]] Vector2f GetVelocity() const;

        Entity& operator--();
        bool operator==(const Entity& other) const;

        virtual void Move();

    };

}
