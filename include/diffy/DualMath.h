#pragma once

#include "Concepts.h"
#include "Dual.h"

#include <cmath>

namespace diffy
{

template<Numeric T>
constexpr Dual<T> sin(const Dual<T>& x)
{
    using std::sin, std::cos;
    return Dual<T>(sin(x.value()), x.derivative() * cos(x.value()));
}

template<Numeric T>
constexpr Dual<T> cos(const Dual<T>& x)
{
    using std::cos, std::sin;
    return Dual<T>(cos(x.value()), -x.derivative() * sin(x.value()));
}

template<Numeric T>
constexpr Dual<T> tan(const Dual<T>& x)
{
    using std::tan, std::cos;
    constexpr T cosValue = cos(x.value());
    return Dual<T>(tan(x.value()), x.derivative() / (cosValue * cosValue));
}

template<Numeric T>
constexpr Dual<T> cot(const Dual<T>& x)
{
    using std::tan, std::cos;
    constexpr T sinValue = sin(x.value());
    return Dual<T>(1 / tan(x.value()), -x.derivative() / (sinValue * sinValue));
}

template<Numeric T>
constexpr Dual<T> exp(const Dual<T>& x)
{
    using std::exp;
    constexpr T expValue = exp(x.value());
    return Dual<T>(expValue, x.derivative() * expValue);
}

} // namespace diffy
