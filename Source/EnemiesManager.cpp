#include "Headers/EnemiesManager.hpp"

#include "../Core/GameLogic/GameConfig.hpp"

EnemiesManager::EnemiesManager()
{
    manager_.reserve(maxEnemies);
}

void EnemiesManager::addMoveable(const size_t level)
{   
    auto direction = static_cast<float>(getRandom() % 180) - 90.f;
    if(direction < 0)
    {
        direction = 360 + direction;
    }
    manager_.push_back(std::make_shared<Sprite>(Game::Vector2f(static_cast<float>(getRandom()), -20.f),
                                                direction,
                                                Game::Vector2u{30, 30},
                                                level * 1.f,
                                                level * 1.f));
}

void EnemiesManager::addSelfSteering()
{
    manager_.push_back(std::make_shared<SelfSteering>(Game::Vector2f(static_cast<float>(getRandom()),
                                                        static_cast<float>(Game::Config::ScreenHeight) -1.f )));
}

void EnemiesManager::clearEnemies()
{
    
    for(auto& sprite : manager_)
    {
        if(sprite->GetPosition().x < 0 or
           sprite->GetPosition().x > Game::Config::ScreenWidth ||
           sprite->GetPosition().y > Game::Config::ScreenHeight)
        {
            sprite->Kill();
        }  
    }
    auto it = std::remove_if(manager_.begin(), manager_.end(), [&](const auto& sprite)
            {
                return (sprite->GetHP() <= 0 and sprite->getCounter() >= 4);
            });
    
   manager_.erase(it, manager_.end());
}

void EnemiesManager::drawAll(sf::RenderWindow& i_window)
{
    for(auto& sprite : manager_)
    {
        sprite->draw(i_window);
        if(sprite->GetHP() <= 0 && sprite->getCounter() <= 4)
        {   
            sf::Sprite boom;
            sf::Texture texture;
            texture.loadFromFile("Images/Boom.png");
            boom.setPosition(sf::Vector2f(sprite->GetPosition().x - 15, sprite->GetPosition().y - 15));
            boom.setTexture(texture);
            boom.setTextureRect(sf::IntRect(30 * sprite->getCounter(), 0, 30, 30));
            i_window.draw(boom);            
            sprite->increaseCounter();
        }
    }
}

void EnemiesManager::organizeEnemies(const size_t level, const Spaceship& target)
{
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - previousEnemyRelease).count();
    
    if(deltaTime > 100 && manager_.size() < maxEnemies)
    {
        if(level >= 2 && getRandom() % (100/(level*2)) == 0)
        {
            addSelfSteering();  
        }
        else
        {
            addMoveable(level);
        }
        previousEnemyRelease = std::chrono::steady_clock::now();
    }   

    for(auto& sprite : manager_)
    {   
        //temporary manager to check collision with other enemies
        auto temporaryManager = manager_;
        temporaryManager.erase(std::remove(temporaryManager.begin(), temporaryManager.end(), sprite), temporaryManager.end());

        if(auto selfSteering = dynamic_pointer_cast<SelfSteering>(sprite))
        {
            selfSteering->aimTarget(target);
            selfSteering->regulateDirection();
            selfSteering->Move();
            sprite->Hit(temporaryManager);
        }
        else
        {
            dynamic_pointer_cast<Sprite>(sprite)->Move();
        }
    }
}

void EnemiesManager::reset()
{
    manager_.erase(manager_.begin(), manager_.end());
}

int EnemiesManager::getRandom()
{
    std::random_device randDev;
    std::mt19937 randGenerator(randDev());
    std::uniform_int_distribution<int> distribution(50, Game::Config::ScreenWidth - 50);
    return distribution(randGenerator);
}

Manager& EnemiesManager::getManager()
{
    return this-> manager_;
}

