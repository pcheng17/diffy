#include <doctest/doctest.h>
#include <diffy/Dual.h>

using namespace diffy;

TEST_SUITE("Dual numbers basic operations")
{
    TEST_CASE("Construction")
    {
        SUBCASE("Default constructor")
        {
            Dual<double> d;
            CHECK(d.value() == 0.0);
            CHECK(d.derivative() == 0.0);
        }

        SUBCASE("Value constructor")
        {
            Dual<double> d(3.0);
            CHECK(d.value() == 3.0);
            CHECK(d.derivative() == 0.0);
        }

        SUBCASE("Value and derivative constructor")
        {
            Dual<double> d(3.0, 2.0);
            CHECK(d.value() == 3.0);
            CHECK(d.derivative() == 2.0);
        }

        SUBCASE("Variable helper")
        {
            auto v = toVariable(5.0);
            CHECK(v.value() == 5.0);
            CHECK(v.derivative() == 1.0);
        }

        SUBCASE("Constant helper")
        {
            auto c = toConstant(5.0);
            CHECK(c.value() == 5.0);
            CHECK(c.derivative() == 0.0);
        }
    }
}
