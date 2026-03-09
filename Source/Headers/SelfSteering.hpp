#pragma once
#ifndef SELFSTEERING
#define SELFSTEERING

#include <cmath>
#include <cstdlib>
#include <memory>
#include <random>
#include <vector>
#include <iostream>

#include "Controllable.hpp"
#include "EnemiesManager.hpp"

class SelfSteering : public Controllable
{
protected:
    Game::Vector2f targetPosition_{0.f, 0.f};
    float targetDirection_ = 180.f;
    float warningDistance_ = 200.f;
public:
    SelfSteering(const Game::Vector2f& position_);
    virtual ~SelfSteering() = default;
    
    void aimWithoutCollision(const Sprite& target,const std::vector<std::shared_ptr<Sprite>> obstacles);
    virtual void aimTarget(const Sprite& sprite);
    virtual void aimTarget(const std::shared_ptr<Sprite>& sprite_ptr);
    void draw(sf::RenderWindow& i_window) override;
    virtual void regulateDirection();
    
    int getRandom();

};
#endif

