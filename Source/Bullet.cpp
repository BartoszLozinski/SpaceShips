#include "Headers/Bullet.hpp"

Bullet::Bullet(const Game::Vector2u& position_, const float rotation_, const Game::Vector2u& size_, const float maxSpeed_, const float speed_)
    : Sprite(position_, rotation_, size_, maxSpeed_, speed_)
{}

/*
Bullet::Bullet(sf::Vector2f position, float rotation)
    : Bullet(position, rotation, sf::Vector2f(10.f, 10.f), 15.f, 15.f)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(rotation);
}
*/
void Bullet::draw(sf::RenderWindow& i_window)
{
    sf::Texture texture;
    texture.loadFromFile("Images/Bullet.png");

    sprite_.setTexture(texture);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });

    i_window.draw(sprite_);
}

