#include "Headers/Sprite.hpp"

Sprite::Sprite(sf::Vector2f position, float rotation, sf::Vector2f size)
    : position_(position)
    , size_(size)
{   
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(rotation);
}

Sprite::Sprite(sf::Vector2f position, float rotation)
    : position_(position)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(rotation);
}

Sprite::Sprite()
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
}

Sprite::Sprite(sf::Vector2f position)
    : Sprite(position, 0)
{
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
}

bool Sprite::checkCollision(const std::shared_ptr<Sprite>& sprite)
{   
    bool status = false;
    if(sprite_.getGlobalBounds().intersects(
            sprite->getSprite().getGlobalBounds()
                ))
    {
        status = true;
    }
    return status;
}

bool Sprite::checkSpritesCollision(std::vector<std::shared_ptr<Sprite>>& vectorOfSprites)
{   
    bool CollisionStatus = false;
    for(auto& sprite : vectorOfSprites)
    {   
        if(checkCollision(sprite))
        {
            HP_--;
            sprite->setHP(sprite->getHP() - 1);
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
    sprite_.setPosition(position_);
    
    i_window.draw(sprite_);
}

bool Sprite::isInMap()
{
    //checking if the center of the sprite is inside the map
    if(position_.x >= 0 and position_.x <= SCREEN_WIDTH and
       position_.y >= 0 and position_.y <= SCREEN_HEIGHT)
    {   
        return true;
    }
    else
    {   
        return false;
    }
}

/*____________________GETTERS___________________________*/

size_t Sprite::getCounter() const
{
    return this->counter_;
}

int Sprite::getHP() const
{
    return this->HP_;
}

sf::Vector2f Sprite::getPosition() const
{
    return this->position_;
}

float Sprite::getRotation() const
{
    return this->sprite_.getRotation();
}

sf::Vector2f Sprite::getSize() const
{
    return this->size_;
}

sf::Sprite Sprite::getSprite() const
{
    return this->sprite_;
}

sf::Vector2f Sprite::getVelocity() const
{
    return this->velocity_;
}

/*__________________SETTERS___________________________*/

void Sprite::increaseCounter()
{
    counter_++;
}

void Sprite::setPosition(sf::Vector2f const newPos)
{
    position_ = newPos;
}

void Sprite::setHP(int const hp)
{
    HP_ = hp;
}

void Sprite::setRotation(float const rotation)
{
    sprite_.setRotation(rotation);
}

void Sprite::setSize(sf::Vector2f const size)
{
    size_ = size;
}

/*______________________OPERATORS_______________________*/

Sprite& Sprite::operator--()
{
    HP_--;
    return *this;
}

bool Sprite::operator==(const Sprite& other) const
{
    return position_ == other.position_;
}

