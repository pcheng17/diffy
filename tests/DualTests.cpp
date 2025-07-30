#include <doctest/doctest.h>
#include <diffy/Dual.h>

using namespace diffy;

TEST_SUITE("Dual number tests")
{
    TEST_CASE("Construct dual numbers")
    {
        Dual<double> d1;
        double expectedValue;
        double expectedDerivative;

        SUBCASE("Default constructor")
        {
            d1 = Dual<double>();
            expectedValue = 0;
            expectedDerivative = 0;
        }

        SUBCASE("Value constructor")
        {
            d1 = Dual<double>(3.0);
            expectedValue = 3.0;
            expectedDerivative = 0.0;
        }

        SUBCASE("Value and derivative constructor")
        {
            d1 = Dual<double>(3.0, 2.0);
            expectedValue = 3.0;
            expectedDerivative = 2.0;
        }

        SUBCASE("Variable helper")
        {
            d1 = toVariable(static_cast<double>(5.0));
            expectedValue = 5.0;
            expectedDerivative = 1.0;
        }

        SUBCASE("Constant helper")
        {
            d1 = toConstant(static_cast<double>(5.0));
            expectedValue = 5.0;
            expectedDerivative = 0.0;
        }

        CHECK(d1.value() == expectedValue);
        CHECK(d1.derivative() == expectedDerivative);
    }

    TEST_CASE("Unary operations")
    {
        constexpr Dual<double> d1(3.0, 2.0);
        Dual<double> result, expected;

        SUBCASE("Unary plus")
        {
            result = +d1;
            expected = Dual<double>(3.0, 2.0);
        }

        SUBCASE("Unary minus")
        {
            result = -d1;
            expected = Dual<double>(-3.0, -2.0);
        }

        CHECK(result == expected);
    }

    TEST_CASE("Binary operations with dual numbers")
    {
        constexpr Dual<double> d1(3.0, 2.0);
        constexpr Dual<double> d2(-4.0, 1.0);
        Dual<double> result1, expected;

        SUBCASE("Addition")
        {
            result1 = d1 + d2;
            expected = Dual<double>(-1.0, 3.0);
        }

        SUBCASE("Accumulative addition")
        {
            result1 = d1;
            result1 += d2;
            expected = Dual<double>(-1.0, 3.0);
        }

        SUBCASE("Subtraction")
        {
            result1 = d1 - d2;
            expected = Dual<double>(7.0, 1.0);
        }

        SUBCASE("Accumulative subtraction")
        {
            result1 = d1;
            result1 -= d2;
            expected = Dual<double>(7.0, 1.0);
        }

        SUBCASE("Multiplication")
        {
            result1 = d1 * d2;
            expected = Dual<double>(-12.0, -5.0);
        }

        SUBCASE("Accumulative multiplication")
        {
            result1 = d1;
            result1 *= d2;
            expected = Dual<double>(-12.0, -5.0);
        }

        SUBCASE("Division")
        {
            result1 = d1 / d2;
            expected = Dual<double>(-0.75, -0.6875);
        }

        SUBCASE("Accumulative division")
        {
            result1 = d1;
            result1 /= d2;
            expected = Dual<double>(-0.75, -0.6875);
        }

        CHECK(result1 == expected);
    }

    TEST_CASE("Binary operations with scalars")
    {
        constexpr Dual<double> d1(4.0, 2.0);
        double scalar = 5.0;
        Dual<double> result1, expected;

        SUBCASE("Addition with scalar on the right")
        {
            result1 = d1 + scalar;
            expected = Dual<double>(9.0, 2.0);
        }

        SUBCASE("Addition with scalar on the left")
        {
            result1 = scalar + d1;
            expected = Dual<double>(9.0, 2.0);
        }

        SUBCASE("Accumulative addition")
        {
            result1 = d1;
            result1 += scalar;
            expected = Dual<double>(9.0, 2.0);
        }

        SUBCASE("Subtraction with scalar on the right")
        {
            result1 = d1 - scalar;
            expected = Dual<double>(-1.0, 2.0);
        }

        SUBCASE("Subtraction with scalar on the left")
        {
            result1 = scalar - d1;
            expected = Dual<double>(1.0, -2.0);
        }

        SUBCASE("Accumulative subtraction")
        {
            result1 = d1;
            result1 -= scalar;
            expected = Dual<double>(-1.0, 2.0);
        }

        SUBCASE("Multiplication with scalar on the right")
        {
            result1 = d1 * scalar;
            expected = Dual<double>(20.0, 10.0);
        }

        SUBCASE("Multiplication with scalar on the left")
        {
            result1 = scalar * d1;
            expected = Dual<double>(20.0, 10.0);
        }

        SUBCASE("Accumulative multiplication")
        {
            result1 = d1;
            result1 *= scalar;
            expected = Dual<double>(20.0, 10.0);
        }

        SUBCASE("Division with scalar on the right")
        {
            result1 = d1 / scalar;
            expected = Dual<double>(0.8, 0.4);
        }

        SUBCASE("Division with scalar on the left")
        {
            result1 = scalar / d1;
            expected = Dual<double>(1.25, -0.625);
        }

        SUBCASE("Accumulative division")
        {
            result1 = d1;
            result1 /= scalar;
            expected = Dual<double>(0.8, 0.4);
        }

        CHECK(result1 == expected);
    }
}
