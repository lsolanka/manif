#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <manif/manif.h>

using TestState = manif::Bundle<double, manif::R3, manif::SO3>;
using SO3 = manif::SO3<double>;
using Eigen::Vector3d;

Eigen::Vector3d f_manif_so3_issue(const TestState& x, const Eigen::Vector3d& vec)
{
    const auto R = x.element<1>();
    //std::cerr << "R" << R.rotation() << std::endl;

    const auto vec_rotated = R.rotation() * vec;

    return vec_rotated;
}

TEST(Manif, testRotationIssue)
{
    auto x = TestState::Identity();
    x.element<1>() = SO3(Eigen::Quaterniond{1, 0, 0, 0}.normalized());
    Vector3d vec = {1, 2, 3};

    auto vec_rotated = f_manif_so3_issue(x, vec);

    EXPECT_FLOAT_EQ(vec_rotated[0], 1);
    EXPECT_FLOAT_EQ(vec_rotated[1], 2);
    EXPECT_FLOAT_EQ(vec_rotated[2], 3);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
