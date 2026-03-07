#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Source/Headers/Sprite.hpp"
#include "Source/Headers/Moveable.hpp"
#include "Source/Headers/Controllable.hpp"
#include "Source/Headers/Bullet.hpp"
#include "Source/Headers/Spaceship.hpp"
#include "Source/Headers/SelfSteering.hpp"


class SelfSteeringFixture : public testing::TestWithParam<std::tuple<sf::Vector2f,float>>
{
public:
    //by default it points 180 deg which means up direction
    SelfSteering selfSteering{sf::Vector2f(500, 500)};
protected:
};

struct SelfSteeringMock : public SelfSteering
{
    SelfSteeringMock(sf::Vector2f position) : SelfSteering(position){};
    MOCK_METHOD(void, aimTarget, (const Sprite& target), (override));
    MOCK_METHOD(void, regulateDirection, (), (override));
};

struct SelfSteeringMockFixture : public testing::TestWithParam<std::tuple<sf::Vector2f,float>>
{
    SelfSteeringMock selfSteeringMock{sf::Vector2f(500.f, 400.f)};
    const std::vector<std::shared_ptr<Sprite>> obstacles {std::make_shared<Sprite>(sf::Vector2f(400.f, 300.f))
                                                         ,std::make_shared<Sprite>(sf::Vector2f(700.f, 200.f))};

};


TEST(BulletsTest, killingTest)
{
    Spaceship ship1;
    ship1.getBulletManager().push_back(std::make_shared<Bullet>(sf::Vector2f(200, 500), 0));
    ship1.getBulletManager().push_back(std::make_shared<Bullet>(sf::Vector2f(200, 500), 0));
    ship1.getBulletManager().push_back(std::make_shared<Bullet>(sf::Vector2f(200, 500), 0));

    ship1.getBulletManager()[1]->setPosition(sf::Vector2f(-10, 500));
    ship1.updatePosition();
    ship1.organizeBullets();

    ASSERT_EQ(2, ship1.getBulletManager().size());
}

TEST(SpriteCollision, positiveTest1)
{   
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(sf::Vector2f(200, 200));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(sf::Vector2f(215, 210));
    
    //Window required for proper collision checking
    //worked without it with rectangleShape, but not with sprites
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TEST");
    sprite1->draw(window);
    sprite2->draw(window);
    
    ASSERT_TRUE(sprite1->checkCollision(sprite2));
}

TEST(SpriteCollision, positiveTest2)
{
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(sf::Vector2f(200, 200));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(sf::Vector2f(229, 229));
    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TEST");
    sprite1->draw(window);
    sprite2->draw(window);

    ASSERT_TRUE(sprite1->checkCollision(sprite2));
}

TEST(SpriteCollision, negativeTest1)
{
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(sf::Vector2f(200, 200));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(sf::Vector2f(235, 229));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TEST");
    sprite1->draw(window);
    sprite2->draw(window);

    ASSERT_FALSE(sprite1->checkCollision(sprite2));
}


TEST(SpriteCollision, negativeTest2)
{
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(sf::Vector2f(170, 170));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(sf::Vector2f(200, 200));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TEST");
    sprite1->draw(window);
    sprite2->draw(window);

    ASSERT_FALSE(sprite1->checkCollision(sprite2));
}

TEST_P(SelfSteeringFixture, regualteDirTest_turnLeft)
{
    std::tuple<sf::Vector2f, float> tuple = GetParam();
    
    Sprite sprite(std::get<0>(tuple));
    selfSteering.aimTarget(sprite);
    selfSteering.regulateDirection();
    float expectedValue = std::get<1>(tuple);

    ASSERT_EQ(expectedValue, selfSteering.getRotation());
}


TEST_F(SelfSteeringMockFixture, aimWithoutCollisionTest)
{
    Sprite target(sf::Vector2f{600, 400});
    EXPECT_CALL(selfSteeringMock, aimTarget(target)).Times(1);
    EXPECT_CALL(selfSteeringMock, regulateDirection()).Times(1);
    selfSteeringMock.aimWithoutCollision(target, obstacles);
}


INSTANTIATE_TEST_SUITE_P(RotationEQ, SelfSteeringFixture, testing::Values(
    std::make_tuple(sf::Vector2f(600, 400), 185),
    std::make_tuple(sf::Vector2f(600, 600), 185),
    std::make_tuple(sf::Vector2f(501, 600), 185),
    std::make_tuple(sf::Vector2f(499, 600), 175),
    std::make_tuple(sf::Vector2f(300, 600), 175),
    std::make_tuple(sf::Vector2f(300, 400), 175),
    std::make_tuple(sf::Vector2f(500, 200), 180)));

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

