#include "Headers/Bullet.hpp"

Bullet::Bullet(const Game::Vector2f& position_, const float rotation_, const Game::Vector2u& size_, const float maxSpeed_, const float speed_)
    : Sprite(position_, rotation_, size_, maxSpeed_, speed_)
{}

void Bullet::draw(sf::RenderWindow& i_window)
{
    sf::Texture texture;
    texture.loadFromFile("Images/Bullet.png");

    sprite_.setTexture(texture);
    sprite_.setPosition({ position.x, position.y });
    sprite_.setRotation(rotation);

    i_window.draw(sprite_);
}

