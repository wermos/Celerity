#ifndef CONSTEXPR_HPP
#define CONSTEXPR_HPP

#include <cstddef> // for the libstdc++ macros (if any)

/**
 * TODO: Fill this out.
*/
#if defined(__GLIBCXX__) && __GLIBCXX__ >= 20210923L
 	/* Using GNU GCC libstdc++, so using also its STL implementation */
	#define CMATH_CONSTEXPR constexpr
#else
	#define CMATH_CONSTEXPR
#endif // __GLIBCXX__

#endif // CONSTEXPR_HPP