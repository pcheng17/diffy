#pragma once

#include <concepts>
#include <cmath>
#include <type_traits>

namespace diffy
{

// Concept to constrain numeric types
template<typename T>
concept Numeric = std::floating_point<T> || std::integral<T>;

// Forward declaration
template<Numeric T>
class Dual;

// Type trait to check if something is a Dual
template<typename T>
struct isDual : std::false_type {};

template<Numeric T>
struct isDual<Dual<T>> : std::true_type {};

template<typename T>
constexpr bool is_dual_v = isDual<T>::value;

/// @brief A class representing dual numbers for automatic differentiation.
template<Numeric T>
class Dual
{
public:
    using ValueType = T;

    constexpr Dual() : mValue(T{0}), mDeriv(T{0}) {}
    constexpr explicit Dual(T value) : mValue(value), mDeriv(T{0}) {}
    constexpr Dual(T value, T derivative) : mValue(value), mDeriv(derivative) {}

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

    // constexpr Dual& operator/=(const Dual& other) {
    //     T new_derivative = (derivative_ * other.value_ - value_ * other.derivative_)
    //                       / (other.value_ * other.value_);
    //     value_ /= other.value_;
    //     derivative_ = new_derivative;
    //     return *this;
    // }
    //
    // // Scalar operations
    // constexpr Dual& operator+=(T scalar) {
    //     value_ += scalar;
    //     return *this;
    // }
    //
    // constexpr Dual& operator-=(T scalar) {
    //     value_ -= scalar;
    //     return *this;
    // }
    //
    // constexpr Dual& operator*=(T scalar) {
    //     value_ *= scalar;
    //     derivative_ *= scalar;
    //     return *this;
    // }
    //
    // constexpr Dual& operator/=(T scalar) {
    //     value_ /= scalar;
    //     derivative_ /= scalar;
    //     return *this;
    // }
    //
    // // Comparison operators (only compare values)
    // constexpr bool operator==(const Dual& other) const {
    //     return value_ == other.value_;
    // }
    //
    // constexpr bool operator!=(const Dual& other) const {
    //     return value_ != other.value_;
    // }
    //
    // constexpr bool operator<(const Dual& other) const {
    //     return value_ < other.value_;
    // }
    //
    // constexpr bool operator<=(const Dual& other) const {
    //     return value_ <= other.value_;
    // }
    //
    // constexpr bool operator>(const Dual& other) const {
    //     return value_ > other.value_;
    // }
    //
    // constexpr bool operator>=(const Dual& other) const {
    //     return value_ >= other.value_;
    // }

private:
    T mValue;
    T mDeriv;
};

// Binary arithmetic operators
// template<Numeric T>
// constexpr Dual<T> operator+(const Dual<T>& lhs, const Dual<T>& rhs) {
//     return Dual<T>(lhs.value() + rhs.value(), lhs.derivative() + rhs.derivative());
// }
//
// template<Numeric T>
// constexpr Dual<T> operator-(const Dual<T>& lhs, const Dual<T>& rhs) {
//     return Dual<T>(lhs.value() - rhs.value(), lhs.derivative() - rhs.derivative());
// }
//
// template<Numeric T>
// constexpr Dual<T> operator*(const Dual<T>& lhs, const Dual<T>& rhs) {
//     return Dual<T>(lhs.value() * rhs.value(),
//                    lhs.derivative() * rhs.value() + lhs.value() * rhs.derivative());
// }
//
// template<Numeric T>
// constexpr Dual<T> operator/(const Dual<T>& lhs, const Dual<T>& rhs) {
//     T value = lhs.value() / rhs.value();
//     T derivative = (lhs.derivative() * rhs.value() - lhs.value() * rhs.derivative())
//                    / (rhs.value() * rhs.value());
//     return Dual<T>(value, derivative);
// }
//
// // Scalar-dual operations
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator+(const Dual<T>& dual, U scalar) {
//     return Dual<T>(dual.value() + scalar, dual.derivative());
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator+(U scalar, const Dual<T>& dual) {
//     return dual + scalar;
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator-(const Dual<T>& dual, U scalar) {
//     return Dual<T>(dual.value() - scalar, dual.derivative());
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator-(U scalar, const Dual<T>& dual) {
//     return Dual<T>(scalar - dual.value(), -dual.derivative());
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator*(const Dual<T>& dual, U scalar) {
//     return Dual<T>(dual.value() * scalar, dual.derivative() * scalar);
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator*(U scalar, const Dual<T>& dual) {
//     return dual * scalar;
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator/(const Dual<T>& dual, U scalar) {
//     return Dual<T>(dual.value() / scalar, dual.derivative() / scalar);
// }
//
// template<Numeric T, Numeric U>
// constexpr Dual<T> operator/(U scalar, const Dual<T>& dual) {
//     T value = scalar / dual.value();
//     T derivative = -scalar * dual.derivative() / (dual.value() * dual.value());
//     return Dual<T>(value, derivative);
// }
//
// // Stream output
// template<Numeric T>
// std::ostream& operator<<(std::ostream& os, const Dual<T>& dual) {
//     return os << std::format("({}, {})", dual.value(), dual.derivative());
// }
//

// Helper function to create a variable (dual number with derivative = 1)
template<Numeric T>
constexpr Dual<T> toVariable(T value) {
    return Dual<T>(value, T{1});
}

// Helper function to create a constant (dual number with derivative = 0)
template<Numeric T>
constexpr Dual<T> toConstant(T value) {
    return Dual<T>(value, T{0});
}

} // namespace diffy
