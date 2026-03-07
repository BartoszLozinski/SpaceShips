#include "Headers/SelfSteering.hpp"

SelfSteering::SelfSteering()
    : Controllable()
{   
    setSize(Game::Vector2u(15, 30));
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
    sprite_.setRotation(180.f);
    speed = 11.f;
    rotationSpeed = 5.f;
}

SelfSteering::SelfSteering(const Game::Vector2u& position)
    : Controllable(position)
{   
    setSize(Game::Vector2u(15, 30));
    sprite_.setOrigin(size.x/2, size.y/2);
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });
    sprite_.setRotation(180.f);
    speed = 11.f;
    rotationSpeed = 5.f;
}

void SelfSteering::aimWithoutCollision(const Sprite& target, const std::vector<std::shared_ptr<Sprite>> obstacles)
{   
    aimTarget(target);
    regulateDirection();

    targetPosition_ = target.GetPosition();
    targetDirection_ = atan((position.x - targetPosition_.x) 
                             / (targetPosition_.y - position.y)) * (180.f / M_PI);

    for(auto& obstacle : obstacles)
    {
        auto distance = pow(
                        pow((obstacle->GetPosition().x - position.x),2) + 
                        pow((obstacle->GetPosition().y - position.y),2),0.5);

        if(distance < warningDistance_)
        {
            std::cout << "Warning!!!\n";
            auto predictedDistance = pow(
                        pow((obstacle->GetPosition().x + obstacle->GetVelocity().x
                        - position.x - velocity.x),2) + 
                        pow((obstacle->GetPosition().y + obstacle->GetVelocity().x
                        - position.y - velocity.y),2)
                                    ,0.5);

            if(predictedDistance < distance)
            {   
                //predicting turning left
                auto predictedDirection = (sprite_.getRotation() - rotationSpeed) * M_PI / 180.f;
                auto predictedVelocity = velocity;
                predictedVelocity.x = round(-speed * sin(predictedDirection));
                predictedVelocity.y = round(speed * cos(predictedDirection));

                auto predictedLeft = pow(
                        pow((obstacle->GetPosition().x + obstacle->GetVelocity().x
                        - position.x - predictedVelocity.x),2) + 
                        pow((obstacle->GetPosition().y + obstacle->GetVelocity().x
                        - position.y - predictedVelocity.y),2)
                                    ,0.5);

                //predicting turning right
                predictedDirection = (sprite_.getRotation() + rotationSpeed) * M_PI / 180.f;
                predictedVelocity.x = round(-speed * sin(predictedDirection));
                predictedVelocity.y = round(speed * cos(predictedDirection));

                auto predictedRight = pow(
                        pow((obstacle->GetPosition().x + obstacle->GetVelocity().x
                        - position.x - predictedVelocity.x),2) + 
                        pow((obstacle->GetPosition().y + obstacle->GetVelocity().x
                        - position.y - predictedVelocity.y),2)
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
    targetPosition_ = sprite.GetPosition();
    targetDirection_ = atan((position.x - targetPosition_.x) 
                             / (targetPosition_.y - position.y)) * (180.f / M_PI);

    if(targetPosition_.y < position.y)
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
    targetPosition_ = sprite_ptr->GetPosition();
    targetDirection_ = atan((position.x - targetPosition_.x) 
                             / (targetPosition_.y - position.y)) * (180.f / M_PI);

    if(targetPosition_.y < position.y)
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
    sprite_.setPosition({ static_cast<float>(position.x), static_cast<float>(position.y) });

    i_window.draw(sprite_);
}

void SelfSteering::regulateDirection()
{
    auto rotationDifference = 0.f;
    
    rotationDifference = GetRotation() - targetDirection_;
 
    //turn left or right
    
    if(GetRotation() > targetDirection_ and
       GetRotation() - targetDirection_ <= 180.f and
       GetRotation() - targetDirection_ > 0.f)
    {
        rotationDifference = GetRotation() - targetDirection_;
        if(rotationDifference < rotationSpeed)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnLeft();
        }
    }
    
    else if(GetRotation() > targetDirection_ and
            GetRotation() - targetDirection_ > 180.f)
    {
        rotationDifference = GetRotation() - targetDirection_ - 180.f;
        if(rotationDifference < rotationSpeed)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnRight();
        }
    }
    
    else if(GetRotation() < targetDirection_ and
            GetRotation() - targetDirection_ < 0.f and
            GetRotation() - targetDirection_ > -180.f)
    {
        rotationDifference = targetDirection_ - GetRotation();
        if(rotationDifference < rotationSpeed)
        {
            sprite_.setRotation(targetDirection_);
        }
        else
        {
            turnRight();
        }
    }
    
    else if(GetRotation() < targetDirection_ and
            GetRotation() - targetDirection_ < 0.f)
    {
        rotationDifference = targetDirection_ - GetRotation();
        if(rotationDifference < rotationSpeed)
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

