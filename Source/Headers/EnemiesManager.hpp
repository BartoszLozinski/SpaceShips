#pragma once
#ifndef ENEMIESMANAGER
#define ENEMIESMANAGER

#include "Moveable.hpp"
#include "Bullet.hpp"
#include "SelfSteering.hpp"
#include "Spaceship.hpp"

#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <thread>

using Manager = std::vector<std::shared_ptr<Sprite>>;
using Time = std::chrono::time_point<std::chrono::steady_clock>;
class EnemiesManager
{
protected:
    unsigned deltaTime = 200;
    Manager manager_;
    unsigned maxEnemies = 30;
    Time previousEnemyRelease; 
public:
    EnemiesManager();
    ~EnemiesManager() = default;
    void addMoveable(const size_t level);
    void addSelfSteering();
    void clearEnemies();
    void drawAll(sf::RenderWindow& i_window);
    void organizeEnemies(const size_t level, const Spaceship& target);
    void reset();

    Manager& getManager();
    int getRandom();
};

#endif

