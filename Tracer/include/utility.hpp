#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <limits>
#include <random>
#include <numbers>

// Constants

inline constexpr double infinity = std::numeric_limits<double>::infinity();

// Utility Functions

inline double degreesToRadians(double degrees) {
    return (degrees * std::numbers::pi) / 180.0;
}

inline double randomDouble() {
    // Returns a random real in [0,1).
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937_64 generator;

    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
	static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937_64 generator;

    return distribution(generator);
}

#endif // UTILITY_HPP
