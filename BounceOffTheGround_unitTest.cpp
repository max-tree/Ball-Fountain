#include "physics.h"
#include "gtest/gtest.h"

//TEST(BounceOffTheGround, WhenBallVelocityisZeroAndInContactWithTheGround_ExpectNoChange)
//{
//    std::array <double, 3> expectedPosition{0.0,0.0,-0.0109};
//    std::array <double, 3> initialPosition{0.0,0.0,0.0};
//    std::array <double, 3> resultantPosition{0.0,0.0,0.0};
//    physics v;
//    double tolerance{0.001};

//    v.setPosition(initialPosition);
//    v.change_position();
//    resultantPosition = v.getPosition();

//    EXPECT_NEAR(expectedPosition[0],resultantPosition[0], tolerance);
//    EXPECT_NEAR(expectedPosition[1],resultantPosition[1], tolerance);
//    EXPECT_NEAR(expectedPosition[2],resultantPosition[2], tolerance);
//}
