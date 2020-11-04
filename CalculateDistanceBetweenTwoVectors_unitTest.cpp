#include "Physics.h"
#include "gtest/gtest.h"

TEST(CalculateDistance, WhenTwoVectorsAreTheSame_ExpectDistanceOfZero)
{
    double expectedResult{0.0};
    double result{0.0};
    double tolerance{0.001};
    std::array <double, 3> vector1{0.0,0.0,0.0};
    std::array <double, 3> vector2{0.0,0.0,0.0};

    result = calculate_distance_between_two_vectors(vector1, vector2);
    EXPECT_NEAR(expectedResult, result, tolerance);
}

TEST(CalculateDistance, WhenTwoVectorsAreDifferent_ExpectCorrectDistance)
{
    double expectedResult{1.732};
    double result{0.0};
    double tolerance{0.001};
    std::array <double, 3> vector1{1.0,1.0,1.0};
    std::array <double, 3> vector2{0.0,0.0,0.0};

    result = calculate_distance_between_two_vectors(vector1, vector2);
    EXPECT_NEAR(expectedResult, result, tolerance);
}
