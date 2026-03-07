#include "Headers/Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, float rotation, sf::Vector2f size, float maxSpeed, float speed)
    : Moveable(position, rotation, size, maxSpeed, speed)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(rotation);
}

Bullet::Bullet(sf::Vector2f position, float rotation)
    : Bullet(position, rotation, sf::Vector2f(10.f, 10.f), 15.f, 15.f)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(rotation);
}

void Bullet::draw(sf::RenderWindow& i_window)
{
    sf::Texture texture;
    texture.loadFromFile("Images/Bullet.png");

    sprite_.setTexture(texture);
    sprite_.setPosition(position_);

    i_window.draw(sprite_);
}

