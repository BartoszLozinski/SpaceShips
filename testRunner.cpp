#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Source/Headers/Sprite.hpp"
#include "Source/Headers/Controllable.hpp"
#include "Source/Headers/Bullet.hpp"
#include "Source/Headers/Spaceship.hpp"
#include "Source/Headers/SelfSteering.hpp"
#include "Core/GameLogic/GameConfig.hpp"

class SelfSteeringFixture : public testing::TestWithParam<std::tuple<Game::Vector2u,float>>
{
public:
    //by default it points 180 deg which means up direction
    SelfSteering selfSteering{Game::Vector2u(500, 500)};
protected:
};

struct SelfSteeringMock : public SelfSteering
{
    SelfSteeringMock(Game::Vector2u position) : SelfSteering(position){};
    MOCK_METHOD(void, aimTarget, (const Sprite& target), (override));
    MOCK_METHOD(void, regulateDirection, (), (override));
};

struct SelfSteeringMockFixture : public testing::TestWithParam<std::tuple<Game::Vector2u,float>>
{
    SelfSteeringMock selfSteeringMock{Game::Vector2u(500.f, 400.f)};
    const std::vector<std::shared_ptr<Sprite>> obstacles {std::make_shared<Sprite>(Game::Vector2u(400.f, 300.f))
                                                         ,std::make_shared<Sprite>(Game::Vector2u(700.f, 200.f))};

};


TEST(BulletsTest, killingTest)
{
    Spaceship ship1;
    ship1.getBulletManager().push_back(std::make_shared<Bullet>(Game::Vector2u(-10, 500), 0));
    ship1.getBulletManager().push_back(std::make_shared<Bullet>(Game::Vector2u(200, 500), 0));
    ship1.getBulletManager().push_back(std::make_shared<Bullet>(Game::Vector2u(200, 500), 0));

    ship1.Move();
    ship1.organizeBullets();

    ASSERT_EQ(2, ship1.getBulletManager().size());
}

TEST(SpriteCollision, positiveTest1)
{   
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(Game::Vector2u(200, 200));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(Game::Vector2u(215, 210));
        
    ASSERT_TRUE(sprite1->CheckCollision(*sprite2));
}

TEST(SpriteCollision, positiveTest2)
{
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(Game::Vector2u(200, 200));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(Game::Vector2u(230, 230));

    ASSERT_TRUE(sprite1->CheckCollision(*sprite2));
}

TEST(SpriteCollision, negativeTest1)
{
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(Game::Vector2u(200, 200));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(Game::Vector2u(235, 229));

    ASSERT_FALSE(sprite1->CheckCollision(*sprite2));
}


TEST(SpriteCollision, negativeTest2)
{
    std::shared_ptr<Sprite> sprite1 = std::make_shared<Sprite>(Game::Vector2u(170, 170));
    std::shared_ptr<Sprite> sprite2 = std::make_shared<Sprite>(Game::Vector2u(201, 201));

    ASSERT_FALSE(sprite1->CheckCollision(*sprite2));
}

TEST_P(SelfSteeringFixture, regualteDirTest_turnLeft)
{
    std::tuple<Game::Vector2u, float> tuple = GetParam();
    
    Sprite sprite(std::get<0>(tuple));
    selfSteering.aimTarget(sprite);
    selfSteering.regulateDirection();
    float expectedValue = std::get<1>(tuple);

    ASSERT_EQ(expectedValue, selfSteering.GetRotation());
}


TEST_F(SelfSteeringMockFixture, aimWithoutCollisionTest)
{
    Sprite target(Game::Vector2u{600, 400});
    EXPECT_CALL(selfSteeringMock, aimTarget(target)).Times(1);
    EXPECT_CALL(selfSteeringMock, regulateDirection()).Times(1);
    selfSteeringMock.aimWithoutCollision(target, obstacles);
}


INSTANTIATE_TEST_SUITE_P(RotationEQ, SelfSteeringFixture, testing::Values(
    std::make_tuple(Game::Vector2u(600, 400), 185),
    std::make_tuple(Game::Vector2u(600, 600), 185),
    std::make_tuple(Game::Vector2u(501, 600), 185),
    std::make_tuple(Game::Vector2u(499, 600), 175),
    std::make_tuple(Game::Vector2u(300, 600), 175),
    std::make_tuple(Game::Vector2u(300, 400), 175),
    std::make_tuple(Game::Vector2u(500, 200), 180)));


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

