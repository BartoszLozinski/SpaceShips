#include "Headers/SelfSteering.hpp"

SelfSteering::SelfSteering()
{   
    setSize(sf::Vector2f(15.f, 30.f));
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(180.f);
    speed_ = 11.f;
    rotationSpeed_ = 5.f;
}

SelfSteering::SelfSteering(sf::Vector2f position)
    : Controllable(position)
{   
    setSize(sf::Vector2f(15.f, 30.f));
    sprite_.setOrigin(size_.x/2, size_.y/2);
    sprite_.setPosition(position_);
    sprite_.setRotation(180.f);
    speed_ = 11.f;
    rotationSpeed_ = 5.f;
}

void SelfSteering::aimWithoutCollision(const Sprite& target, const std::vector<std::shared_ptr<Sprite>> obstacles)
{   
    aimTarget(target);
    regulateDirection();

    targetPosition_ = target.getPosition();
    targetDirection_ = atan((position_.x - targetPosition_.x) 
                             / (targetPosition_.y - position_.y)) * (180.f / M_PI);

    for(auto& obstacle : obstacles)
    {
        auto distance = pow(
                        pow((obstacle->getPosition().x - position_.x),2) + 
                        pow((obstacle->getPosition().y - position_.y),2),0.5);

        if(distance < warningDistance_)
        {
            std::cout << "Warning!!!\n";
            auto predictedDistance = pow(
                        pow((obstacle->getPosition().x + obstacle->getVelocity().x
                        - position_.x - velocity_.x),2) + 
                        pow((obstacle->getPosition().y + obstacle->getVelocity().x
                        - position_.y - velocity_.y),2)
                                    ,0.5);

            if(predictedDistance < distance)
            {   
                //predicting turning left
                auto predictedDirection = (sprite_.getRotation() - rotationSpeed_) * M_PI / 180.f;
                auto predictedVelocity = velocity_;
                predictedVelocity.x = round(-speed_ * sin(predictedDirection));
                predictedVelocity.y = round(speed_ * cos(predictedDirection));

                auto predictedLeft = pow(
                        pow((obstacle->getPosition().x + obstacle->getVelocity().x
                        - position_.x - predictedVelocity.x),2) + 
                        pow((obstacle->getPosition().y + obstacle->getVelocity().x
                        - position_.y - predictedVelocity.y),2)
                                    ,0.5);

                //predicting turning right
                predictedDirection = (sprite_.getRotation() + rotationSpeed_) * M_PI / 180.f;
                predictedVelocity.x = round(-speed_ * sin(predictedDirection));
                predictedVelocity.y = round(speed_ * cos(predictedDirection));

                auto predictedRight = pow(
                        pow((obstacle->getPosition().x + obstacle->getVelocity().x
                        - position_.x - predictedVelocity.x),2) + 
                        pow((obstacle->getPosition().y + obstacle->getVelocity().x
                        - position_.y - predictedVelocity.y),2)
                                    ,0.5);
                
                if(predictedLeft < predictedRight)
                {
                    turnRight();
                }
                else
                {
                    turnLeft();
                }
                std::cout << "Collision probable!!!!!!\n";
            }
        }
    }

}

void SelfSteering::aimTarget(const Sprite& sprite)
{
    targetPosition_ = sprite.getPosition();
    targetDirection_ = atan((position_.x - targetPosition_.x) 
                             / (targetPosition_.y - position_.y)) * (180.f / M_PI);

    if(targetPosition_.y < position_.y)
    {
        targetDirection_ += 180.f;
    }

    if(targetDirection_ < 0)
    {
        targetDirection_ += 360.f;
    }
}

void SelfSteering::aimTarget(const std::shared_ptr<Sprite>& sprite_ptr)
{
    targetPosition_ = sprite_ptr->getPosition();
    targetDirection_ = atan((position_.x - targetPosition_.x) 
                             / (targetPosition_.y - position_.y)) * (180.f / M_PI);

    if(targetPosition_.y < position_.y)
    {
        targetDirection_ += 180.f;
    }

    if(targetDirection_ < 0)
    {
        targetDirection_ += 360.f;
    }
}

void SelfSteering::draw(sf::RenderWindow& i_window)
{
    sf::Texture texture;
    texture.loadFromFile("Images/Rocket.png");

    sprite_.setTexture(texture);
    sprite_.setPosition(position_);

    i_window.draw(sprite_);
}

void SelfSteering::regulateDirection()
{
    auto rotationDifference = 0.f;
    
    rotationDifference = getRotation() - targetDirection_;
 
    //turn left or right
    
    if(getRotation() > targetDirection_ and
       getRotation() - targetDirection_ <= 180.f and
       getRotation() - targetDirection_ > 0.f)
    {
        rotationDifference = getRotation() - targetDirection_;
        if(rotationDifference < rotationSpeed_)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnLeft();
        }
    }
    
    else if(getRotation() > targetDirection_ and
            getRotation() - targetDirection_ > 180.f)
    {
        rotationDifference = getRotation() - targetDirection_ - 180.f;
        if(rotationDifference < rotationSpeed_)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnRight();
        }
    }
    
    else if(getRotation() < targetDirection_ and
            getRotation() - targetDirection_ < 0.f and
            getRotation() - targetDirection_ > -180.f)
    {
        rotationDifference = targetDirection_ - getRotation();
        if(rotationDifference < rotationSpeed_)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnRight();
        }
    }
    
    else if(getRotation() < targetDirection_ and
            getRotation() - targetDirection_ < 0.f)
    {
        rotationDifference = targetDirection_ - getRotation();
        if(rotationDifference < rotationSpeed_)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnLeft();
        }
    }
}

int SelfSteering::getRandom()
{
    std::random_device randDev;
    std::mt19937 randGenerator(randDev());
    std::uniform_int_distribution<int> distribution(200, SCREEN_WIDTH - 200);
    return distribution(randGenerator);
}

