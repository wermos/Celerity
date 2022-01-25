#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <limits>
#include <random>
#include <numbers>

#include "float.hpp"


// Constants

inline constexpr Float infinity = std::numeric_limits<Float>::infinity();

// Utility Functions

inline Float degreesToRadians(Float degrees) {
	return (degrees * std::numbers::pi) / 180.0;
}

inline Float randomDouble() {
	// Returns a random real in [0,1].
	static std::uniform_real_distribution<Float> distribution(0.0, std::nextafter(1.0));
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
			static std::mt19937_64 generator;
#else
			static std::mt19937 generator;
#endif

	return distribution(generator);
}

inline Float randomDouble(Float min, Float max) {
	// Returns a random real in [min, max].
	static std::uniform_real_distribution<Float> distribution(min, std::nextafter(max));
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
	static std::mt19937_64 generator;
#else
	static std::mt19937 generator;
#endif

	return distribution(generator);
}

#endif // UTILITY_HPP
