#pragma once

constexpr double relEps{ 1e-8 };
constexpr double absEps{ 1e-12 };

constexpr bool approximatelyEqualRel(double a, double b, double relEpsilon) noexcept;
constexpr bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon);
