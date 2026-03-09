#pragma once
#ifndef SPRITE
#define SPRITE

#include <memory>

#include <SFML/Graphics.hpp>

#include "../../Core/GameLogic/Entity.hpp"

class Sprite : public Game::Entity
{
protected:
    sf::Sprite sprite_;
    size_t counter_ = 0;

public:
    Sprite(const Game::Vector2f& position_ = { 200.f, 300.f }, const float rotation_ = 0.f, const Game::Vector2u& size_ = { 30, 30 }, const float maxSpeed_ = 6.0f, const float speed_ = 0.f);

    virtual ~Sprite() = default;
    
    virtual bool checkSpritesCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites);
    virtual void draw(sf::RenderWindow& i_window);

    size_t getCounter() const;
    sf::Sprite getSprite() const;
    
    void increaseCounter();
    void setRotation(float const rotation);
};
#endif

