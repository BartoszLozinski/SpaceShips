#include "Entity.hpp"
#include "GameConfig.hpp"

#include <cmath>

namespace Game
{
    Entity::Entity(const Vector2f& position_, const float rotation_, const Vector2u& size_, const float maxSpeed_, const float speed_)
        : position(position_)
        , rotation(rotation_)
        , size(size_)
        , maxSpeed(maxSpeed_)
        , speed(speed_)
    {};

    bool Entity::CheckCollision(const Entity& other) const
    {
        const auto otherPosition = other.GetPosition();
        const auto otherSize = other.GetSize();
    
        return std::fabs(position.x - otherPosition.x) <= (size.x / 2 + otherSize.x / 2) &&
               std::fabs(position.y - otherPosition.y) <= (size.y / 2 + otherSize.y / 2);
    }

    int Entity::GetHP() const { return HP; }
    Vector2f Entity::GetPosition() const { return position; }
    float Entity::GetRotation() const { return rotation; }
    Vector2u Entity::GetSize() const { return size; }
    float Entity::GetSpeed() const  { return speed; }
    Vector2f Entity::GetVelocity() const { return velocity; }

    bool Entity::IsInMap() const
    {
        if(position.x >= 0 && position.x <= Game::Config::ScreenWidth &&
           position.y >= 0 && position.y <= Game::Config::ScreenHeight)
        {   
            return true;
        }
        else
        {   
            return false;
        }
    }

    void Entity::Move()
    {
        velocity.x = -speed * std::sin(rotation);
        velocity.y = speed * std::cos(rotation);
        position += velocity;
    }

    Entity& Entity::operator--()
    {
        HP--;
        return *this;
    }

    bool Entity::operator==(const Entity& other) const
    {
        return position == other.position;
    }

    void Entity::SetHP(const int hp) { HP = hp; }
    void Entity::SetSpeed(const float speed_) { speed = speed_; }

};
