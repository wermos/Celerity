#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <limits>
#include <numbers>

// Constants

inline constexpr double infinity = std::numeric_limits<double>::infinity();

// Utility Functions

inline double degreesToRadians(double degrees) {
    return (degrees * std::numbers::pi) / 180.0;
}

#endif // UTILITY_HPP
