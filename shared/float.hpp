#pragma once

/**
 * This little trick is used by PBRT (https://github.com/mmp/pbrt-v3) and
 * mentioned here: https://pbr-book.org/3ed-2018/Utilities/Main_Include_File
 *
 * Its main advantages are:
 * 	- Making it possible to build versions of the ray tracer using either
 *    representation, and
 * 	- Being able to switch to double for numerically tricky situations as well
 *    as to verify that rounding error with floats isn’t causing errors for a
 *    given scene.
*/
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
typedef double Float;
#else
typedef float Float;
#endif // USE_DOUBLE_AS_FLOAT_TYPE
