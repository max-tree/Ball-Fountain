#include "mainwindow.h"
#include "gtest/gtest.h"
#include <vector>


TEST(WhenVelocityIsZeroInTheHorizontal, ExpectNoChangeInTheHorizontal)
{
    std::vector <double> expectedVelocity{0.0,0.0,0.0};
    std::vector <double> velocity{0.0,0.0,0.0};
    accerlerate_due_to_gravity(velocity);
}
