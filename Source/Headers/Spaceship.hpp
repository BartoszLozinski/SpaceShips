#pragma once
#ifndef SPACESHIP
#define SPACESHIP

#include "Controllable.hpp"
#include "Bullet.hpp"

#include <array>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <random>

class Spaceship : public Controllable
{
protected:
    std::vector<std::shared_ptr<Bullet>> bulletManager_;
    size_t bulletsQuantity_ = 20;
    unsigned deltaTime_ = 0; //ms
    const unsigned invulnerabilityTime_ = 1500; //ms
    unsigned invulnerabilityDT = 0; //ms
    bool invulnerability_ = false;
    size_t maxBulletsQuantity_ = 20;
    bool shootAbility_ = true;
    std::chrono::time_point<std::chrono::steady_clock> previousShootTime_;
    std::chrono::time_point<std::chrono::steady_clock> previousInvulnerabilityTime_;
    const unsigned shootUnabilityTime_ = 150; //ms
    size_t points_ = 0;

public:
    Spaceship();    
    virtual ~Spaceship() = default;
    
    void checkBulletsCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites);
    bool checkSpritesCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites) override;
    void draw(sf::RenderWindow& i_window) override;
    void organizeBullets();
    void shoot();
    void shootBack();
    void updatePosition() override;
    
    size_t getBullets() const;
    std::vector<std::shared_ptr<Bullet>>& getBulletManager();
    size_t getPoints() const;
    int getRandom();
    
    void reset();
};

#endif

