#pragma once
#ifndef BULLET
#define BULLET

#include "Sprite.hpp"
#include <vector>

class Bullet : public Sprite
{
protected:
    size_t damage_ = 1;

public:
    Bullet(const Game::Vector2f& position_ = { 200.f, 300.f }, const float rotation_ = 0.f, const Game::Vector2u& size_ = { 30, 30 }, const float maxSpeed_ = 6.0f, const float speed_ = 0.f);

    virtual ~Bullet() = default;
    void draw(sf::RenderWindow& i_window) override;
};

#endif

