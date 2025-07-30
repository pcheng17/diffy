#pragma once

#include <concepts>

namespace diffy
{
template<typename T>
concept Numeric = std::floating_point<T> || std::integral<T>;

} // namespace diffy
