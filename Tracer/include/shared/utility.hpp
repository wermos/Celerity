#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <limits>
#include <random>
#include <numbers>

/** This little trick is used by PBRT () and mentioned here:
 * https://pbr-book.org/3ed-2018/Utilities/Main_Include_File
 *
 * Its main advantages are:
 * 	- Making it possible to build versions of the ray tracer using either
 *    representation, and
 * 	- Being able to switch to doubles for numerically tricky situations as well
 *    as to verify that rounding error with floats isn’t causing errors for a
 *    given scene.
*/
#ifdef USE_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif // USE_FLOAT_AS_DOUBLE
//TODO: Use this trick everywhere


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
