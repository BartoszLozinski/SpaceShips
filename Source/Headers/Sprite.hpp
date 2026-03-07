#pragma once
#ifndef SPRITE
#define SPRITE

#include <memory>
#include "Global.hpp"
#include <SFML/Graphics.hpp>

#include "../../Core/GameLogic/Entity.hpp"

class Sprite : public Game::Entity
{
protected:
    sf::Sprite sprite_;
    size_t counter_ = 0;
    float maxSpeed = 6.f;
    float speed = 0.f;

public:
    /*
    Sprite();
    Sprite(Game::Vector2u position);
    Sprite(Game::Vector2u position, float rotation);
    Sprite(Game::Vector2u position, float rotation, Game::Vector2u size);
    */
    Sprite(const Game::Vector2f& position_ = { 200.f, 300.f }, const float rotation_ = 0.f, const Game::Vector2u& size_ = { 30, 30 }, const float maxSpeed_ = 6.0f, const float speed_ = 0.f);

    virtual ~Sprite() = default;
    
    virtual bool checkSpritesCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites);
    virtual void draw(sf::RenderWindow& i_window);

    bool isInMap(); 
    
    size_t getCounter() const;
    sf::Sprite getSprite() const;
    
    void increaseCounter();
    void setHP(int const hp);   
    void setPosition(Game::Vector2f const newPos);
    void setSize(Game::Vector2u const size);
    void setRotation(float const rotation);

    void Move() override;

    float getSpeed() const;
    void setSpeed(float newSpeed);

    Sprite& operator--();
    bool operator==(const Sprite& other) const;
};
#endif

