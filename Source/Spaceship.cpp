#include "Headers/Spaceship.hpp"
#include "../Core/GameLogic/GameConfig.hpp"

Spaceship::Spaceship()
    : Controllable(Game::Vector2f(static_cast<float>(Game::Config::ScreenWidth)/2, static_cast<float>(Game::Config::ScreenHeight)/2),
                  180.f, // rotation
                  Game::Vector2u(40, 30), //size
                  9.f, //maxSpeed
                  0.f, //speed
                  3.f) //rotationalSpeed
{
    setHP(5);
    previousInvulnerabilityTime_ = std::chrono::steady_clock::now();
    bulletManager_.reserve(bulletsQuantity_);
       
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ position.x, position.y });
    sprite_.setRotation(rotation);
}

void Spaceship::checkBulletsCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites)
{   
    for(auto& bullet : bulletManager_)
    {
        bullet->checkSpritesCollision(vectorOfSprites);
        if(bullet->GetHP() <= 0 and bullet->IsInMap())
        {   
            points_++;
            if(bulletsQuantity_ < (maxBulletsQuantity_ - 1))
            {
                bulletsQuantity_ += 1;
                if(getRandom() == 1)
                {
                    //50% chance for bonus bullets
                    bulletsQuantity_ += 2;
                    
                    if (bulletsQuantity_ > maxBulletsQuantity_)
                        bulletsQuantity_ = maxBulletsQuantity_;
                }
            }
            else if(bulletsQuantity_ == (maxBulletsQuantity_ - 1))
            {
                bulletsQuantity_ = maxBulletsQuantity_;
            }
        }
    }
}

bool Spaceship::checkSpritesCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites) 
{   
    auto HPbeforeCollision = GetHP();
    auto collisionStatus = false;
    if(Sprite::checkSpritesCollision(vectorOfSprites) and invulnerability_ == false)
    {
        invulnerability_ = true;
        previousInvulnerabilityTime_ = std::chrono::steady_clock::now();
        collisionStatus = true;
    }
    
    else if(Sprite::checkSpritesCollision(vectorOfSprites) and invulnerability_ == true)
    {
        this->HP = HPbeforeCollision;
        collisionStatus = true;
    }

    invulnerabilityDT = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - previousInvulnerabilityTime_).count();
        
    if(invulnerabilityDT >= invulnerabilityTime_)
    {
        invulnerability_ = false;
    }

    return collisionStatus;
}

void Spaceship::draw(sf::RenderWindow& i_window)
{
    sf::Texture texture;
    texture.loadFromFile("Images/Spaceship.png");

    sprite_.setTexture(texture);
    sprite_.setPosition({ position.x, position.y });

    i_window.draw(sprite_);
    
    if(speed > 0)
    {
        sf::Sprite light;
        sf::Texture engineTexture;
        engineTexture.loadFromFile("Images/EngineLight.png");
        light.setOrigin(7.5f, 26.f);
        light.setTexture(engineTexture);
        light.setRotation(GetRotation());
        //light.setPosition(sf::Vector2f(position_.x, position_.y - cos(getRotation() * M_PI / 180) * 15));
        light.setPosition(sf::Vector2f{ position.x, position.y });
        light.setTextureRect(sf::IntRect(15 * std::floor(static_cast<int>(speed)/3), 0, 15, 15));
        i_window.draw(light);
    }

    for(auto& bullet : bulletManager_)
    {
        bullet->draw(i_window);
    }
}

void Spaceship::organizeBullets()
{   
    for(auto& bullet : bulletManager_)
    {
        if(bullet->GetHP() <= 0)
        {
            bullet = nullptr;
        }
    }

    auto it = std::remove_if(bulletManager_.begin(), bulletManager_.end(), [&](const auto& bullet)
            {
                return (bullet == nullptr);
            });

    bulletManager_.erase(it, bulletManager_.end());
    maxBulletsQuantity_ = 20 + (points_ / 10) * 10;
}

void Spaceship::reset()
{
    HP = 5;
    position = Game::Vector2f(static_cast<float>(Game::Config::ScreenWidth / 2), static_cast<float>(Game::Config::ScreenHeight / 2));
    bulletsQuantity_ = 20;
    points_ = 0;
    speed = 0.f;
    rotation = 180.f;
    sprite_.setRotation(rotation);
}

void Spaceship::shoot()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
       shootAbility_ && bulletsQuantity_ > 0)
    {
        bulletManager_.push_back(std::make_shared<Bullet>(position, Spaceship::GetRotation()));
        bulletManager_.back()->SetSpeed(11.f);
        previousShootTime_ = std::chrono::steady_clock::now();
        bulletsQuantity_--;
        shootAbility_ = false;
    }

    deltaTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - previousShootTime_).count();
    
    if(deltaTime_ > shootUnabilityTime_)
    {
        shootAbility_ = true;
    }

}

void Spaceship::shootBack()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) and
       shootAbility_ and
       bulletsQuantity_ > 2)
    {   
        std::array<float, 3> rotation = {Spaceship::GetRotation() - 180.f - 45.f,
                                         Spaceship::GetRotation() - 180.f,
                                         Spaceship::GetRotation() - 180.f + 45.f};

        for(auto& value : rotation)
        {   
            bulletManager_.push_back(std::make_shared<Bullet>(position, value));
        }
        previousShootTime_ = std::chrono::steady_clock::now();
        bulletsQuantity_ -= 3;
        shootAbility_ = false;
    }
    
    deltaTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - previousShootTime_).count();

    if(deltaTime_ > shootUnabilityTime_)
    {
        shootAbility_ = true;
    }
}

void Spaceship::Move()
{
    Sprite::Move();

    for(auto& bullet : bulletManager_)
    {
        bullet->Move();
        if(!bullet->IsInMap())
        {
            bullet->setHP(0);
        }
    }
}

size_t Spaceship::getBullets() const
{
    return this->bulletsQuantity_;
}

std::vector<std::shared_ptr<Bullet>>& Spaceship::getBulletManager()
{
    return this->bulletManager_;
}

size_t Spaceship::getPoints() const
{
    return this->points_;
}

int Spaceship::getRandom()
{
    std::random_device randDev;
    std::mt19937 randGenerator(randDev());
    std::uniform_int_distribution<int> distribution(0, 4);
    return distribution(randGenerator);
}

