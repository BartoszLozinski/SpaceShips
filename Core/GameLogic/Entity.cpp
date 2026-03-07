#include "Entity.hpp"

#include <cmath>

namespace Game
{
    Entity::Entity(const Vector2u& position_, const float rotation_, const Vector2u& size_)
        : position(position_)
        , rotation(rotation_)
        , size(size_)
    {};

    /*

    Entity::Entity(const Vector2u& position_, const float rotation_, const Vector2u& size_)
        : position(position_)
        , rotation(rotation_)
        , size(size_)
    {};
    
    Entity::Entity(const Vector2u& position_, const float rotation_)
        : position(position_)
        , rotation(rotation_)
    {};
    
    Entity::Entity(const Vector2u& position_)
        : position(position_)
    {};

    */

    bool Entity::CheckCollision(const Entity& other) const
    {
        const auto otherPosition = other.GetPosition();
        const auto otherSize = other.GetSize();
    
        return std::fabs(position.x - otherPosition.x) <= (size.x / 2 + otherSize.x / 2) &&
               std::fabs(position.y - otherPosition.y) <= (size.y / 2 + otherSize.y / 2);
    }

    int Entity::GetHP() const { return HP; }
    Vector2u Entity::GetPosition() const { return position; }
    float Entity::GetRotation() const { return rotation; }
    Vector2u Entity::GetSize() const { return size; }
    Vector2f Entity::GetVelocity() const { return velocity; }

    Entity& Entity::operator--()
    {
        HP--;
        return *this;
    }

    bool Entity::operator==(const Entity& other) const
    {
        return position == other.position;
    }


};
