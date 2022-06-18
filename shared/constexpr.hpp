#ifndef CONSTEXPR_HPP
#define CONSTEXPR_HPP

#include <cstddef> // for the libstdc++ macros (if any)

/**
 * In C++20, the functions in the cmath header are not required to be marked
 * as constexpr. However, if you have a recent enough version of libstdc++
 * (which is the default C++ Standard Library implementation on Linux),
 * it is marked as constexpr anyways (as an extension of sorts).
 *
 * However, libc++ (LLVM's implementation of the Standard Library), and
 * Microsoft's implementation both have the cmath functions as runtime
 * functions (i.e. as functions which cannot be invoked in a constant
 * expression context.)
 *
 * For this reason, if the Standard Library implementation we are using is
 * GNU's, then we mark the functions which use cmath functions in the
 * implmentation as constexpr, and otherwise we don't.
*/
#if defined(__GLIBCXX__) && __GLIBCXX__ >= 20210923L
 	/* Using GNU GCC libstdc++, so also using its STL implementation */
	#define CMATH_CONSTEXPR constexpr
#else
	#define CMATH_CONSTEXPR
#endif // __GLIBCXX__

#endif // CONSTEXPR_HPP
