#pragma once
#ifndef BULLET
#define BULLET

#include "Moveable.hpp"
#include <vector>

class Bullet : public Moveable
{
protected:
    size_t damage_ = 1;

public:
    Bullet(sf::Vector2f position, float rotation);
    Bullet(sf::Vector2f position, float rotation, sf::Vector2f size, float maxSpeed, float speed);
    
    virtual ~Bullet() = default;
    void draw(sf::RenderWindow& i_window) override;
};

#endif

