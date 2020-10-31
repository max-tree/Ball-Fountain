#include "Physics.h"
#include "gtest/gtest.h"

/*Tests are based on a deltaTime of 1/30*/

TEST(CheckIfBallHasHitTheGround, WhenBallslowestPointInTheZDirIsGreaterThanZero_ExpectFalse)
{
    bool expectedResult{false};
    std::array <double, 3> initialVelocity{1.0,1.0,-1.0};
    std::array <double, 3> initialPosition{2.0,2.0,2.0};

    Physics v;

    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);

    v.check_if_ball_has_hit_the_ground();

    EXPECT_EQ(expectedResult,v.ballOnTheGround);
}

TEST(CheckIfBallHasHitTheGround, WhenBallslowestPointInTheZDirIsZeroOrLess_ExpectTrue)
{
    bool expectedResult{true};
    std::array <double, 3> initialVelocity{1.0,1.0,-1.0};
    std::array <double, 3> initialPosition{0.0,0.0,0.0};

    Physics v;

    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);

    v.check_if_ball_has_hit_the_ground();

    EXPECT_EQ(expectedResult,v.ballOnTheGround);
}
