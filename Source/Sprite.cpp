#include "Headers/Sprite.hpp"
#include <cmath>

Sprite::Sprite(const Game::Vector2f& position_, const float rotation_, const Game::Vector2u& size_, const float maxSpeed_, const float speed_)
    : Game::Entity(position_, rotation_, size_, maxSpeed_, speed_)
{
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ position_.x, position_.y });
    sprite_.setRotation(rotation);
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

bool Sprite::Hit(std::vector<Game::Entity>& others)
{
    bool result = false;
    for (auto& other : others)
        result |= Game::Entity::Hit(other);

    return result;
}

bool Sprite::Hit(std::vector<std::shared_ptr<Sprite>>& others)
{
    bool result = false;
    for (auto& other : others)
        result |= Game::Entity::Hit(std::static_pointer_cast<Game::Entity>(other));

    return result;
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

/*__________________SETTERS___________________________*/

void Sprite::increaseCounter()
{
    counter_++;
}

void Sprite::setRotation(float const rotation)
{
    sprite_.setRotation(rotation);
}
