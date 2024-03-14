#pragma once

#include <limits>
#include <numbers>
#include <random>

// Constants
inline constexpr float infinity = std::numeric_limits<float>::infinity();

// Utility Functions
inline float degreesToRadians(float degrees) {
    return (degrees * std::numbers::pi) / 180.0;
}

inline float randomFloat() {
    // Returns a random float in [0, 1].
    static std::uniform_real_distribution<float> distribution(
        0.0, std::nextafter(1.0, std::numeric_limits<float>::infinity()));

    static std::mt19937 generator;

    return distribution(generator);
}

inline float randomFloat(float min, float max) {
    // Returns a random float in [min, max].
    static std::uniform_real_distribution<float> distribution(
        min, std::nextafter(max, std::numeric_limits<float>::infinity()));

    static std::mt19937 generator;

    return distribution(generator);
}
