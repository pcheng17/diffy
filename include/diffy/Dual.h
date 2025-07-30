#pragma once

#include <concepts>
#include <format>
#include <iosfwd>
#include <type_traits>

namespace diffy
{

template<typename T>
concept Numeric = std::floating_point<T> || std::integral<T>;

template<Numeric T>
class Dual;

template<typename T>
struct isDual : std::false_type
{
};

template<Numeric T>
struct isDual<Dual<T>> : std::true_type
{
};

template<typename T>
constexpr bool is_dual_v = isDual<T>::value;

/// @brief A class representing dual numbers for automatic differentiation.
template<Numeric T>
class Dual
{
public:
    using ValueType = T;

    constexpr Dual() = default;
    constexpr explicit Dual(T value)
        : mValue(value), mDeriv(T{0})
    {
    }
    constexpr Dual(T value, T derivative)
        : mValue(value), mDeriv(derivative)
    {
    }

    constexpr T value() const noexcept { return mValue; }
    constexpr T derivative() const noexcept { return mDeriv; }

    constexpr Dual operator+() const { return *this; }
    constexpr Dual operator-() const { return Dual(-mValue, -mDeriv); }

    constexpr Dual& operator+=(const Dual& other)
    {
        mValue += other.mValue;
        mDeriv += other.mDeriv;
        return *this;
    }

    constexpr Dual& operator-=(const Dual& other)
    {
        mValue -= other.mValue;
        mDeriv -= other.mDeriv;
        return *this;
    }

    constexpr Dual& operator*=(const Dual& other)
    {
        mDeriv = mDeriv * other.mValue + mValue * other.mDeriv;
        mValue *= other.mValue;
        return *this;
    }

    constexpr Dual& operator/=(const Dual& other)
    {
        mDeriv = (mDeriv * other.mValue - mValue * other.mDeriv) / (other.mValue * other.mValue);
        mValue /= other.mValue;
        return *this;
    }

    constexpr Dual& operator+=(T scalar)
    {
        mValue += scalar;
        return *this;
    }

    constexpr Dual& operator-=(T scalar)
    {
        mValue -= scalar;
        return *this;
    }

    constexpr Dual& operator*=(T scalar)
    {
        mValue *= scalar;
        mDeriv *= scalar;
        return *this;
    }

    constexpr Dual& operator/=(T scalar)
    {
        mValue /= scalar;
        mDeriv /= scalar;
        return *this;
    }

private:
    T mValue = 0;
    T mDeriv = 0;
};

/// @brief Create a variable (dual number with derivative = 1)
template<Numeric T>
constexpr Dual<T> toVariable(T value)
{
    return Dual<T>(value, T{1});
}

/// @brief Create a constant (dual number with derivative = 0)
template<Numeric T>
constexpr Dual<T> toConstant(T value)
{
    return Dual<T>(value, T{0});
}

template<Numeric T>
constexpr bool operator==(const Dual<T>& lhs, const Dual<T>& rhs)
{
    return lhs.value() == rhs.value() && lhs.derivative() == rhs.derivative();
}

template<Numeric T>
constexpr Dual<T> operator+(const Dual<T>& lhs, const Dual<T>& rhs)
{
    auto tmp = lhs;
    return tmp += rhs;
}

template<Numeric T>
constexpr Dual<T> operator-(const Dual<T>& lhs, const Dual<T>& rhs)
{
    auto tmp = lhs;
    return tmp -= rhs;
}

template<Numeric T>
constexpr Dual<T> operator*(const Dual<T>& lhs, const Dual<T>& rhs)
{
    auto tmp = lhs;
    return tmp *= rhs;
}

template<Numeric T>
constexpr Dual<T> operator/(const Dual<T>& lhs, const Dual<T>& rhs)
{
    auto tmp = lhs;
    return tmp /= rhs;
}

template<Numeric T>
constexpr Dual<T> operator+(const Dual<T>& dual, T scalar)
{
    auto tmp = dual;
    return tmp += scalar;
}

template<Numeric T>
constexpr Dual<T> operator+(T scalar, const Dual<T>& dual)
{
    return dual + scalar;
}

template<Numeric T>
constexpr Dual<T> operator-(const Dual<T>& dual, T scalar)
{
    auto tmp = dual;
    return tmp -= scalar;
}

template<Numeric T>
constexpr Dual<T> operator-(T scalar, const Dual<T>& dual)
{
    auto tmp = toConstant(scalar);
    return tmp -= dual;
}

template<Numeric T>
constexpr Dual<T> operator*(const Dual<T>& dual, T scalar)
{
    auto tmp = dual;
    return tmp *= scalar;
}

template<Numeric T>
constexpr Dual<T> operator*(T scalar, const Dual<T>& dual)
{
    return dual * scalar;
}

template<Numeric T>
constexpr Dual<T> operator/(const Dual<T>& dual, T scalar)
{
    auto tmp = dual;
    return tmp /= scalar;
}

template<Numeric T>
constexpr Dual<T> operator/(T scalar, const Dual<T>& dual)
{
    auto tmp = toConstant(scalar);
    return tmp / dual;
}

// Stream output
template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Dual<T>& dual)
{
    return os << std::format("({}, {})", dual.value(), dual.derivative());
}

} // namespace diffy
