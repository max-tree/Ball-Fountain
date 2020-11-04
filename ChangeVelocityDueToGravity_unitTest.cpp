#include "Physics.h"
#include "gtest/gtest.h"

/*Tests are based on a deltaTime of 1/30*/

std::array <double,3> get_new_velocity(Physics v, std::array <double,3> initialVelocity)
{
    v.setVelocity(initialVelocity);
    v.change_velocity_due_to_gravity();
    return v.getVelocity();
}

void test_velocity_vector_to_see_if_correct_result_is_output(std::array <double, 3> expectedVelocity, std::array <double, 3> resultantVelocity, double tolerance)
{
    EXPECT_NEAR(expectedVelocity[0],resultantVelocity[0], tolerance);
    EXPECT_NEAR(expectedVelocity[1],resultantVelocity[1], tolerance);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2], tolerance);
}

TEST(ChangeVelocityDueToGravity, WhenVelocityIsZeroInitiallyInTheHorizontal_ExpectNoChangeInTheHorizontal)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,-0.327};
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    double tolerance{0.001};
    Physics v;

    resultantVelocity = get_new_velocity(v, initialVelocity);

    test_velocity_vector_to_see_if_correct_result_is_output(expectedVelocity,resultantVelocity, tolerance);
}

TEST(AccelerationDueToGravityTest, WhenVelocityIsNonzeroInTheHorizontal_ExpectNoChangeInTheHorizontal)
{
    std::array <double, 3> expectedVelocity{1.0,1.0,-0.327};
    std::array <double, 3> initialVelocity{1.0,1.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    double tolerance{0.001};
    Physics v;

    resultantVelocity = get_new_velocity(v, initialVelocity);

    test_velocity_vector_to_see_if_correct_result_is_output(expectedVelocity,resultantVelocity, tolerance);
}

TEST(AccelerationDueToGravityTest, WhenVelocityIsZeroInitiallyInTheVertical_ExpectCorrectResult)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,-0.327};
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    double tolerance{0.001};
    Physics v;

    resultantVelocity = get_new_velocity(v, initialVelocity);

    test_velocity_vector_to_see_if_correct_result_is_output(expectedVelocity,resultantVelocity, tolerance);
}

TEST(AccelerationDueToGravityTest, WhenVelocityIsInitiallyInTheVertical_ExpectCorrectResult)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity{0.0,0.0,0.327};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    double tolerance{0.001};
    Physics v;

    resultantVelocity = get_new_velocity(v, initialVelocity);

    test_velocity_vector_to_see_if_correct_result_is_output(expectedVelocity,resultantVelocity, tolerance);
}
