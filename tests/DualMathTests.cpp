#include <doctest/doctest.h>
#include <diffy/DualMath.h>
#include <vector>

using namespace diffy;

TEST_SUITE("Dual math tests")
{
    TEST_CASE("sin")
    {
        Dual<double> x;
        Dual<double> result, expected;

        // clang-format off
        const std::vector<std::pair<double, Dual<double>>> testCases = {
            {0.0,        Dual<double>(0.0, 1.0)},
            {M_PI / 6,   Dual<double>(0.5, std::sqrt(3) / 2.0)},
            {M_PI / 4,   Dual<double>(std::sqrt(2) / 2, std::sqrt(2) / 2)},
            {M_PI / 3,   Dual<double>(std::sqrt(3) / 2, 1.0 / 2)},
            {M_PI_2,     Dual<double>(1.0, 0.0)},
            {M_PI,       Dual<double>(0.0, -1.0)},
            {3 * M_PI_2, Dual<double>(-1.0, 0.0)},
            {2 * M_PI,   Dual<double>(0.0, 1.0)}
        };
        // clang-format on

        for (const auto& [value, expectedResult] : testCases)
        {
            x = toVariable(value);
            result = sin(x);
            expected = expectedResult;

            CAPTURE(value);
            CAPTURE(result.value());
            CAPTURE(result.derivative());
            CAPTURE(expected.value());
            CAPTURE(expected.derivative());
            CHECK(result.value() == doctest::Approx(expected.value()));
            CHECK(result.derivative() == doctest::Approx(expected.derivative()));
        }
    }

    TEST_CASE("cos")
    {
        Dual<double> x;
        Dual<double> result, expected;

        // clang-format off
        const std::vector<std::pair<double, Dual<double>>> testCases = {
            {0.0,        Dual<double>(1.0, 0.0)},
            {M_PI / 6,   Dual<double>(std::sqrt(3) / 2.0, -1.0 / 2)},
            {M_PI / 4,   Dual<double>(std::sqrt(2) / 2, -std::sqrt(2) / 2)},
            {M_PI / 3,   Dual<double>(1.0 / 2, -std::sqrt(3) / 2)},
            {M_PI_2,     Dual<double>(0.0, -1.0)},
            {M_PI,       Dual<double>(-1.0, 0.0)},
            {3 * M_PI_2, Dual<double>(0.0, 1.0)},
            {2 * M_PI,   Dual<double>(1.0, 0.0)}
        };
        // clang-format on

        for (const auto& [value, expectedResult] : testCases)
        {
            x = toVariable(value);
            result = cos(x);
            expected = expectedResult;

            CAPTURE(value);
            CAPTURE(result.value());
            CAPTURE(result.derivative());
            CAPTURE(expected.value());
            CAPTURE(expected.derivative());
            CHECK(result.value() == doctest::Approx(expected.value()));
            CHECK(result.derivative() == doctest::Approx(expected.derivative()));
        }
    }

    TEST_CASE("tan")
    {
        Dual<double> x;
        Dual<double> result, expected;

        // clang-format off
        const std::vector<std::pair<double, Dual<double>>> testCases = {
            {0.0,        Dual<double>(0.0, 1.0)},
            {M_PI / 6,   Dual<double>(std::sqrt(3) / 3.0, 4.0 / 3.0)},
            {M_PI / 4,   Dual<double>(1.0, 2.0)},
            {M_PI / 3,   Dual<double>(std::sqrt(3), 4.0)},
            {M_PI,       Dual<double>(0.0, 1.0)},
            {2 * M_PI,   Dual<double>(0.0, 1.0)}
        };
        // clang-format on

        for (const auto& [value, expectedResult] : testCases)
        {
            x = toVariable(value);
            result = tan(x);
            expected = expectedResult;

            CAPTURE(value);
            CAPTURE(result.value());
            CAPTURE(result.derivative());
            CAPTURE(expected.value());
            CAPTURE(expected.derivative());
            CHECK(result.value() == doctest::Approx(expected.value()));
            CHECK(result.derivative() == doctest::Approx(expected.derivative()));
        }
    }

    TEST_CASE("cot")
    {
        Dual<double> x;
        Dual<double> result, expected;

        // clang-format off
        const std::vector<std::pair<double, Dual<double>>> testCases = {
            {M_PI / 6,   Dual<double>(std::sqrt(3), -4.0)},
            {M_PI / 4,   Dual<double>(1.0, -2.0)},
            {M_PI / 3,   Dual<double>(std::sqrt(3) / 3.0, -4.0 / 3.0)},
            {M_PI / 2,   Dual<double>(0.0, -1.0)},
        };
        // clang-format on

        for (const auto& [value, expectedResult] : testCases)
        {
            x = toVariable(value);
            result = cot(x);
            expected = expectedResult;

            CAPTURE(value);
            CAPTURE(result.value());
            CAPTURE(result.derivative());
            CAPTURE(expected.value());
            CAPTURE(expected.derivative());
            CHECK(result.value() == doctest::Approx(expected.value()));
            CHECK(result.derivative() == doctest::Approx(expected.derivative()));
        }
    }

    TEST_CASE("exp")
    {
        Dual<double> x;
        Dual<double> result, expected;

        // clang-format off
        const std::vector<std::pair<double, Dual<double>>> testCases = {
            {0.0,        Dual<double>(1.0, 1.0)},
            {1.0,        Dual<double>(std::exp(1.0), std::exp(1.0))},
            {2.0,        Dual<double>(std::exp(2.0), std::exp(2.0))},
            {-1.0,       Dual<double>(std::exp(-1.0), std::exp(-1.0))}
        };
        // clang-format on

        for (const auto& [value, expectedResult] : testCases)
        {
            x = toVariable(value);
            result = exp(x);
            expected = expectedResult;

            CAPTURE(value);
            CAPTURE(result.value());
            CAPTURE(result.derivative());
            CAPTURE(expected.value());
            CAPTURE(expected.derivative());
            CHECK(result.value() == doctest::Approx(expected.value()));
            CHECK(result.derivative() == doctest::Approx(expected.derivative()));
        }
    }
}
