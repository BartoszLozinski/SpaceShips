#include "Headers/Sprite.hpp"
#include <cmath>

Sprite::Sprite(const Game::Vector2f& position_, const float rotation_, const Game::Vector2u& size_, const float maxSpeed_, const float speed_)
    : Game::Entity(position_, rotation_, size_)
    , maxSpeed(maxSpeed_)
    , speed(speed_)
{
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ position_.x, position_.y });
    sprite_.setRotation(rotation);
}

/*
Sprite::Sprite(Game::Vector2u position, float rotation, Game::Vector2u size)
    : Sprite(position, rotation, size)
{   
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
    sprite_.setRotation(rotation);
}

Sprite::Sprite(Game::Vector2u position, float rotation)
    : Entity(position, rotation)
{
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
    sprite_.setRotation(rotation);
}

Sprite::Sprite()
    : Entity()
{
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
}

Sprite::Sprite(Game::Vector2u position)
    : Entity(position)
{
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
}
*/

bool Sprite::checkSpritesCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites)
{   
    bool CollisionStatus = false;
    for(auto& sprite : vectorOfSprites)
    {   
        if(CheckCollision(*sprite))
        {
            HP--;
            --*sprite;
            CollisionStatus = true;
        }
    }
    return CollisionStatus;
}

void Sprite::draw(sf::RenderWindow& i_window)
{
    sf::Texture texture;
    texture.loadFromFile("Images/Sprite.png");

    sprite_.setTexture(texture);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
    sprite_.setRotation(rotation);
    
    i_window.draw(sprite_);
}

bool Sprite::isInMap()
{
    //checking if the center of the sprite is inside the map
    if(position.x >= 0 && position.x <= SCREEN_WIDTH &&
       position.y >= 0 && position.y <= SCREEN_HEIGHT)
    {   
        return true;
    }
    else
    {   
        return false;
    }
}

void Sprite::Move()
{
    float angle = sprite_.getRotation() * M_PI / 180; // deg to radians
    using namespace std;
    {
    velocity.x = round(-speed * sin(angle));
    velocity.y = round(speed * cos(angle));
    }
    position += velocity;    
}

/*____________________GETTERS___________________________*/

size_t Sprite::getCounter() const
{
    return this->counter_;
}

sf::Sprite Sprite::getSprite() const
{
    return this->sprite_;
}

float Sprite::getSpeed() const
{
    return this->speed;
}

/*__________________SETTERS___________________________*/

void Sprite::increaseCounter()
{
    counter_++;
}

void Sprite::setPosition(Game::Vector2f const newPos)
{
    position = newPos;
}

void Sprite::setHP(int const hp)
{
    HP = hp;
}

void Sprite::setRotation(float const rotation)
{
    sprite_.setRotation(rotation);
}

void Sprite::setSize(Game::Vector2u const size)
{
    this->size = size;
}

void Sprite::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

/*______________________OPERATORS_______________________*/

Sprite& Sprite::operator--()
{
    HP--;
    return *this;
}

bool Sprite::operator==(const Sprite& other) const
{
    return position == other.position;
}

