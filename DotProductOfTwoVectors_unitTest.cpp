#include "Physics.h"
#include "gtest/gtest.h"

TEST(DotProductOfTwoVecotrs, WhenOneVectorIsNull_ExpectZero)
{
    double expectedResult{0.0};
    double result{0.0};
    double tolerance{0.001};
    std::array <double, 3> vector1{1.0,1.0,1.0};
    std::array <double, 3> vector2{0.0,0.0,0.0};

    result = dot_product_of_two_vectors(vector1, vector2);
    EXPECT_NEAR(expectedResult, result, tolerance);

}

TEST(DotProductOfTwoVecotrs, WhenTwoVectorsAreDifferent_ExpectCorrectDistance)
{
    double expectedResult{6};
    double result{0.0};
    double tolerance{0.001};
    std::array <double, 3> vector1{1.0,1.0,1.0};
    std::array <double, 3> vector2{2.0,2.0,2.0};

    result = dot_product_of_two_vectors(vector1, vector2);
    EXPECT_NEAR(expectedResult, result, tolerance);

}
