#include "Physics.h"
#include "gtest/gtest.h"

/*Tests are based on a deltaTime of 1/30*/

std::array <double,3> get_new_position(Physics v, std::array <double,3> initialVelocity, std::array <double,3> initialPosition)
{
    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);
    v.change_position();
    return v.getPosition();
}

void test_vector_to_see_if_correct_result_is_output(std::array <double, 3> expectedPosition, std::array <double, 3> resultantPosition, double tolerance)
{
    EXPECT_NEAR(expectedPosition[0],resultantPosition[0], tolerance);
    EXPECT_NEAR(expectedPosition[1],resultantPosition[1], tolerance);
    EXPECT_NEAR(expectedPosition[2],resultantPosition[2], tolerance);
}


TEST(ChangePosition, WhenAllVelocityisZero_ExpectCorrectResult)
{
    std::array <double, 3> expectedPosition{0.0,0.0,-0.0109};
    std::array <double, 3> initialPosition{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity{0.0,0.0,-0.0109};
    std::array <double, 3> resultantPosition{0.0,0.0,0.0};
    Physics v;
    double tolerance{0.001};

    resultantPosition = get_new_position(v, initialVelocity, initialPosition);

    test_vector_to_see_if_correct_result_is_output(expectedPosition,resultantPosition, tolerance);
}

TEST(ChangePosition, WhenAllVelocityisInitiallyNonzero_ExpectCorrectResult)
{
    std::array <double, 3> expectedPosition{1.03333,0.96666,1.0224};
    std::array <double, 3> initialPosition{1.0,1.0,1.0};
    std::array <double, 3> initialVelocity{1.0,-1.0,1.0};
    std::array <double, 3> resultantPosition{0.0,0.0,0.0};
    Physics v;
    double tolerance{0.001};

    resultantPosition = resultantPosition = get_new_position(v, initialVelocity, initialPosition);

    test_vector_to_see_if_correct_result_is_output(expectedPosition,resultantPosition, tolerance);
}
