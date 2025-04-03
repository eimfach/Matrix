#pragma once

#include <algorithm>
#include <cmath>

constexpr double relEps{ 1e-8 };
constexpr double absEps{ 1e-12 };

template <typename T>
concept Comparable = requires(T a) {
    { a < 0 } -> std::convertible_to<bool>;
    { a > 0 } -> std::convertible_to<bool>;
};

template <typename Numeric>
concept Negatable = requires(Numeric a) {
    { -a } -> std::same_as<Numeric>;
};

template <typename Numeric>
    requires Comparable<Numeric>&& Negatable<Numeric>
constexpr Numeric constAbs(Numeric t) {
    if (t < 0) {
        return -t;
    }
    else {
        return t;
    }
}

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
constexpr bool approximatelyEqualRel(double a, double b, double relEpsilon) noexcept {
    return (constAbs(a - b) <= (std::max(constAbs(a), constAbs(b)) * relEpsilon));
}

// Return true if the difference between a and b is less than or equal to absEpsilon, or within relEpsilon percent of the larger of a and b
constexpr bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon) {
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if (constAbs(a - b) <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return approximatelyEqualRel(a, b, relEpsilon);
}
